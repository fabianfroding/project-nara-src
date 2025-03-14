// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Abilities/Generic/NaraJumpAbility.h"

#include "GameFramework/Character.h"

void UNaraJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
		Character->Jump();
}

void UNaraJumpAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
		Character->StopJumping();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
