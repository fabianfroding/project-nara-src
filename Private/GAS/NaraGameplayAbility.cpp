// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraGameplayAbility.h"

#include "Kismet/GameplayStatics.h"

void UNaraGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (true /*CanActivateAbility(Handle, ActorInfo, nullptr, nullptr)*/) // TODO: Check how this works, seems to return false by default if no cost or cooldown is set.
	{
		if (ActivationSFX)
		{
			// TODO: If ability has a target or target location, the activation sound should be played at the target location instead.
			UGameplayStatics::PlaySoundAtLocation(this, ActivationSFX, GetAvatarActorFromActorInfo()->GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}
