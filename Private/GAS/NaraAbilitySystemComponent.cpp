// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraAbilitySystemComponent.h"

#include "Core/NaraGameplayTags.h"
#include "GameplayTagContainer.h"

void UNaraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UNaraAbilitySystemComponent::EffectApplied);

	const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1, 
		5.f, 
		FColor::Orange, 
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Health.ToString()));
}

void UNaraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
