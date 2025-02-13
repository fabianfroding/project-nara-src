// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraProjectileAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Projectiles/NaraProjectile.h"
#include "Projectiles/NaraReturningProjectile.h"

void UNaraProjectileAbility::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride)
{
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	//Rotation.Pitch = 0.f;

	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	ANaraProjectile* Projectile = GetWorld()->SpawnActorDeferred<ANaraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()), // Originally this was set to GetOwningActorFromActorInfo(). It makes more sense that the instigator is the avatar actor.
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (ANaraReturningProjectile* ReturningProjectile = Cast<ANaraReturningProjectile>(Projectile))
		ReturningProjectile->SetReturnToTarget(GetAvatarActorFromActorInfo());

	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	Projectile->FinishSpawning(SpawnTransform);
}
