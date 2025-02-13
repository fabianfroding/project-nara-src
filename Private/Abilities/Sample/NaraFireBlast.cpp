// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Abilities/Sample/NaraFireBlast.h"

#include "Libraries/NaraAbilitySystemLibrary.h"
#include "Projectiles/NaraProjectile.h"
#include "Projectiles/NaraReturningProjectile.h"

TArray<ANaraProjectile*> UNaraFireBlast::SpawnProjectiles()
{
	TArray<ANaraProjectile*> Projectiles;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UNaraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());

		APawn* InstigatorPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
		ANaraProjectile* Projectile = GetWorld()->SpawnActorDeferred<ANaraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			InstigatorPawn,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		if (ANaraReturningProjectile* ReturningProjectile = Cast<ANaraReturningProjectile>(Projectile))
			ReturningProjectile->SetReturnToTarget(GetAvatarActorFromActorInfo());

		//Projectile->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->SetOwner(GetAvatarActorFromActorInfo());
		Projectiles.Add(Projectile);
		Projectile->FinishSpawning(SpawnTransform);
	}

	return Projectiles;
}
