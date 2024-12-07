// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraProjectileAbility.h"

#include "Interfaces/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Projectiles/NaraProjectile.h"

void UNaraProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UKismetSystemLibrary::PrintString(this, FString("UNaraProjectileAbility::ActivateAbility C++"), true, true, FLinearColor::Yellow, 3.f);
}

void UNaraProjectileAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		ANaraProjectile* Projectile = GetWorld()->SpawnActorDeferred<ANaraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetAvatarActorFromActorInfo()), // Originally this was set to GetAvatarActorFromActorInfo(). It makes more sense that the instigator is the avatar actor.
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: Give projectile a gameplay effect spec for causing damage.

		Projectile->FinishSpawning(SpawnTransform);
	}
}
