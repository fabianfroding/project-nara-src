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

	FGameplayTag GameplayCue_MeleeImpact;

	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag Damage;
	FGameplayTag Damage_Default;
	FGameplayTag Damage_Projectile;

	FGameplayTag Debuff;
	FGameplayTag Debuff_Slow;
	FGameplayTag Debuff_Stun;

	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;

	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;

	FGameplayTag Cooldown_Player_Attack;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_HandLeft;
	FGameplayTag CombatSocket_HandRight;
	FGameplayTag CombatSocket_Tail;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	FGameplayTag Effects_HitReact;

	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputHeld;
	FGameplayTag Player_Block_InputReleased;

public:
	static const FNaraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
};