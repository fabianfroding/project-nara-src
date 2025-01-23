// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Abilities/Sample/NaraFireBlast.h"

#include "Libraries/NaraAbilitySystemLibrary.h"
#include "Projectiles/NaraFireBlastProjectile.h"

TArray<ANaraFireBlastProjectile*> UNaraFireBlast::SpawnFireBlastProjectiles()
{
	TArray<ANaraFireBlastProjectile*> Projectiles;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UNaraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		ANaraFireBlastProjectile* Projectile = GetWorld()->SpawnActorDeferred<ANaraFireBlastProjectile>(
			FireBlastProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->ReturnToActor = GetAvatarActorFromActorInfo();
		Projectile->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->SetOwner(GetAvatarActorFromActorInfo());
		Projectiles.Add(Projectile);
		Projectile->FinishSpawning(SpawnTransform);
	}

	return Projectiles;
}
