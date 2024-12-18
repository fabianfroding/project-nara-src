// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraAbilitySystemComponent.h"

#include "Core/NaraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GAS/NaraGameplayAbility.h"

void UNaraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UNaraAbilitySystemComponent::EffectApplied); // This delegate only executes on server.

	const FNaraGameplayTags& GameplayTags = FNaraGameplayTags::Get();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Health.ToString()));
}

void UNaraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UNaraGameplayAbility* NaraAbility = Cast<UNaraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(NaraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UNaraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			continue;

		AbilitySpecInputPressed(AbilitySpec);

		if (AbilitySpec.IsActive())
			continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UNaraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			continue;

		AbilitySpecInputReleased(AbilitySpec);
	}
}

void UNaraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
