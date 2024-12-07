// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/** NaraGameplayTags
 * Singleton containing native gameplay tags.
 */

struct FNaraGameplayTags
{
private:
	static FNaraGameplayTags GameplayTags;

public:
	FGameplayTag Attributes_Health;
	FGameplayTag Attributes_MaxHealth;
	FGameplayTag Attributes_Mana;
	FGameplayTag Attributes_MaxMana;
	FGameplayTag Attributes_AttackPower;
	FGameplayTag Attributes_AttackSpeed;
	FGameplayTag Attributes_MoveSpeed;

	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag Damage;

	FGameplayTag Effects_HitReact;

public:
	static const FNaraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
};