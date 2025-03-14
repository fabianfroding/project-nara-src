// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASAbilities/NaraPassiveAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/NaraAbilitySystemComponent.h"

void UNaraPassiveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UNaraAbilitySystemComponent* NaraASC = Cast<UNaraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo())))
	{
		NaraASC->DeactivatePassiveAbility.AddUObject(this, &UNaraPassiveAbility::ReceiveDeactivate);
	}
}

void UNaraPassiveAbility::ReceiveDeactivate(const FGameplayTag& AbilityTag)
{
	if (AbilityTags.HasTagExact(AbilityTag))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}
