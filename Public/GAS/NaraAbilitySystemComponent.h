// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "NaraAbilitySystemComponent.generated.h"

class UGameplayAbility;
class UNaraSaveGame;

DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UNaraAbilitySystemComponent*);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeactivatePassiveAbility, const FGameplayTag& /*AbilityTag*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FActivatePassiveEffect, const FGameplayTag& /*AbilityTag*/, bool /*bActivate*/);

UCLASS()
class NARA_API UNaraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	FEffectAssetTags EffectAssetTags; // NOTE: To be used by widget controller to pass data to UI.

	FAbilitiesGiven AbilitiesGivenDelegate;
	FDeactivatePassiveAbility DeactivatePassiveAbility;
	FActivatePassiveEffect ActivatePassiveEffect;

	bool bStartupAbilitiesGiven = false;

public:
	void AbilityActorInfoSet();

	void AddCharacterAbilitiesFromSaveData(UNaraSaveGame* SaveData);
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);

	UFUNCTION(BlueprintCallable)
	void AddCharacterAbility(const TSubclassOf<UGameplayAbility>& Ability);

	void EquipAbility(const FGameplayTag& AbilityTag);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
	bool IsPassiveAbility(const FGameplayAbilitySpec& Spec) const;

protected:
	void EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
