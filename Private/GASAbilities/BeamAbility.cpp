// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAbilities/BeamAbility.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Libraries/NaraAbilitySystemLibrary.h"

void UBeamAbility::StoreHitDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		HitLocation = HitResult.ImpactPoint;
		HitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UBeamAbility::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UBeamAbility::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if (OwnerCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);
			FHitResult HitResult;
			const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				SocketLocation,
				BeamTargetLocation,
				10.f,
				TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,
				HitResult,
				true);

			if (HitResult.bBlockingHit)
			{
				HitLocation = HitResult.ImpactPoint;
				HitActor = HitResult.GetActor();
			}
		}
	}

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(HitActor))
	{
		if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UBeamAbility::TargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UBeamAbility::TargetDied);
		}
	}
}
