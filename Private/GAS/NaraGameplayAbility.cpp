// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraGameplayAbility.h"

#include "Actors/AreaIndicator.h"
#include "Kismet/GameplayStatics.h"

void UNaraGameplayAbility::ShowAreaIndicator(UMaterialInterface* DecalMaterial)
{
	if (!AreaIndicator)
	{
		// Lazy spawn since we might not always use area indicators for abilities.
		AreaIndicator = GetWorld()->SpawnActor<AAreaIndicator>(AreaIndicatorClass);
		if (DecalMaterial)
		{
			AreaIndicator->SetDecalMaterial(DecalMaterial);
		}
	}
}

void UNaraGameplayAbility::HideAreaIndicator()
{
	if (AreaIndicator)
	{
		AreaIndicator->Destroy();
	}
}

void UNaraGameplayAbility::UpdateAreaIndicatorLocation(const FVector& NewLocation)
{
	if (AreaIndicator)
	{
		AreaIndicator->SetActorLocation(NewLocation);
	}
}

void UNaraGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	StartTime = UGameplayStatics::GetTimeSeconds(this);

	if (true /*CanActivateAbility(Handle, ActorInfo, nullptr, nullptr)*/) // TODO: Check how this works, seems to return false by default if no cost or cooldown is set.
	{
		if (ActivationSFX)
		{
			// TODO: If ability has a target or target location, the activation sound should be played at the target location instead.
			// Consider using cues. See arcane shards BPs.
			UGameplayStatics::PlaySoundAtLocation(this, ActivationSFX, GetAvatarActorFromActorInfo()->GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}
