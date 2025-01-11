// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Projectiles/NaraBoomerangProjectile.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ANaraBoomerangProjectile::ANaraBoomerangProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANaraBoomerangProjectile::BeginPlay()
{
	Super::BeginPlay();
	DefaultSpeed = ProjectileMovement->GetMaxSpeed();
	ClampedDestinationSpeedModifier = FMath::Clamp(DestinationSpeedModifier, 0.f, 1.f);
	ClampedReturnSpeedModifier = FMath::Max(0.f, ClampedReturnSpeedModifier);

	ACharacter* InstigatorCharacter = Cast<ACharacter>(GetInstigator());
	if (InstigatorCharacter)
	{
		CachedInstigatorMesh = InstigatorCharacter->GetMesh();
	}
}

void ANaraBoomerangProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	ElapsedTime += DeltaSeconds;

	if (IsReturning())
	{
		ReturnToInstigator();

		const FVector ReturnLocation = CachedInstigatorMesh 
			? CachedInstigatorMesh->GetSocketLocation(ReturnMeshSocketName) 
			: ProjectileMovement->HomingTargetComponent->GetComponentLocation();

		const float ElapsedReturnTime = ElapsedTime - TimeUntilReturn;
		const float SpeedFactor = UKismetMathLibrary::Lerp((DefaultSpeed * ClampedDestinationSpeedModifier), DefaultSpeed * ClampedReturnSpeedModifier,
			UKismetMathLibrary::SafeDivide(ElapsedReturnTime, TimeUntilReturn));
		ProjectileMovement->Velocity = UKismetMathLibrary::Normal(ReturnLocation - GetActorLocation()) * SpeedFactor;
		ProjectileMovement->MaxSpeed = SpeedFactor;
	}
	else
	{
		const float SpeedFactor = UKismetMathLibrary::Lerp(DefaultSpeed, DefaultSpeed * ClampedDestinationSpeedModifier,
			UKismetMathLibrary::SafeDivide(ElapsedTime, TimeUntilReturn));
		ProjectileMovement->MaxSpeed = SpeedFactor;
		ProjectileMovement->Velocity = UKismetMathLibrary::Normal(ProjectileMovement->Velocity) * SpeedFactor;
	}
}

void ANaraBoomerangProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (IsReturning() && OtherActor == GetInstigator())
		Destroy();
}

void ANaraBoomerangProjectile::ReturnToInstigator()
{
	if (ProjectileMovement->bIsHomingProjectile)
		return;

	ACharacter* InstigatorCharacter = Cast<ACharacter>(GetInstigator());
	if (!InstigatorCharacter)
		return;

	USkeletalMeshComponent* InstigatorMesh = InstigatorCharacter->GetMesh();
	if (!InstigatorMesh)
		return;

	ProjectileMovement->HomingTargetComponent = InstigatorMesh;
	ProjectileMovement->bIsHomingProjectile = true;

	UGameplayStatics::PlaySoundAtLocation(this, ReturnSFX, GetActorLocation());

	if (bResetTargetsOnReturn)
		ResetHitActors();
}
