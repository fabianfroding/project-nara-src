// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Projectiles/NaraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/NaraAbilitySystemLibrary.h"
#include "Nara/Nara.h"
#include "NiagaraFunctionLibrary.h"

ANaraProjectile::ANaraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ANaraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ANaraProjectile::OnSphereOverlap);

	LoopingSFXComponent = UGameplayStatics::SpawnSoundAttached(LoopingSFX, GetRootComponent());
}

void ANaraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!UNaraAbilitySystemLibrary::AreActorsEnemies(DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser(), OtherActor))
		return;

	if (bIgnoreInstigator && (OtherActor == GetInstigator()))
		return;

	if (DamageEffectSpecHandle.Data.IsValid() && DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor)
		return;

	if (!bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSFX, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());
		
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
	}

	if (LoopingSFXComponent != nullptr) LoopingSFXComponent->Stop();

	bHit = true;

	// NOTE: If we want effect to be applied to the source ASC, we can do that here.
	// For example, if projectile hits should give the caster some kind of buff.

	Destroy();
}

void ANaraProjectile::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();
	if (EffectSpec)
		EffectSpec->SetSetByCallerMagnitude(InstantGameplayEffectMagnitudeTag, -1.f);

	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec);
}
