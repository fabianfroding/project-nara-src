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
	FGameplayTag Attributes_Tenacity; // Resistance to move/attack speed reduction.
	FGameplayTag Attributes_Haste; // Increase to cast speed.

	FGameplayTag Attributes_Resistance;
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lighting;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;

	FGameplayTag GameplayCue_MeleeImpact;

	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lighting;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	FGameplayTag Abilities_Attack;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_HandLeft;
	FGameplayTag CombatSocket_HandRight;
	FGameplayTag CombatSocket_Tail;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag Effects_HitReact;

public:
	static const FNaraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
};