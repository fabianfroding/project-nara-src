// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Abilities/Sample/NaraFireBlast.h"

#include "Libraries/NaraAbilitySystemLibrary.h"
#include "Projectiles/NaraReturningProjectile.h"

TArray<ANaraReturningProjectile*> UNaraFireBlast::SpawnFireBlastProjectiles()
{
	TArray<ANaraReturningProjectile*> Projectiles;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UNaraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		ANaraReturningProjectile* Projectile = GetWorld()->SpawnActorDeferred<ANaraReturningProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->SetReturnToTarget(GetAvatarActorFromActorInfo());
		//Projectile->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->SetOwner(GetAvatarActorFromActorInfo());
		Projectiles.Add(Projectile);
		Projectile->FinishSpawning(SpawnTransform);
	}

	return Projectiles;
}
