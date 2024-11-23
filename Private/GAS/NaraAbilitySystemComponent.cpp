// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraAbilitySystemComponent.h"

#include "GameplayTagContainer.h"

void UNaraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UNaraAbilitySystemComponent::EffectApplied);
}

void UNaraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
