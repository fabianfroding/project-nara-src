// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAbilities/BeamAbility.h"

#include "GameFramework/Character.h"

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
