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

void ANaraProjectile::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSFX, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());
	if (LoopingSFX)
	{
		LoopingSFXComponent->Stop();
		LoopingSFXComponent->DestroyComponent();
	}
	bHit = true;
}

void ANaraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	if (SourceAvatarActor == OtherActor)
		return;

	if (!UNaraAbilitySystemLibrary::AreActorsEnemies(SourceAvatarActor, OtherActor))
		return;

	if (!bHit)
		OnHit();
		
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		const bool bKnockback = FMath::RandRange(1, 100) < DamageEffectParams.KnockbackChance;
		if (bKnockback)
		{
			FRotator Rotation = GetActorRotation();
			Rotation.Pitch = 45.f;

			const FVector KnockbackDirection = Rotation.Vector();
			const FVector KnockbackForce = KnockbackDirection * DamageEffectParams.KnockbackForceMagnitude;
			DamageEffectParams.KnockbackForce = KnockbackForce;
		}

		DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
		UNaraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
	}

	// NOTE: If we want effect to be applied to the source ASC, we can do that here.
	// For example, if projectile hits should give the caster some kind of buff.

	if (!bDontDestroyOnImpact)
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
