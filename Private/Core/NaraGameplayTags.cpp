// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameplayTags.h"

#include "GameplayTagsManager.h"

FNaraGameplayTags FNaraGameplayTags::GameplayTags;

void FNaraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Health"));
	GameplayTags.Attributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.MaxHealth"));

	GameplayTags.Attributes_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Mana"), 
		FString("Mana is used as an ambigious term for whatever resource the entity needs to consume to use abilities."));

	GameplayTags.Attributes_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.MaxMana"));
	GameplayTags.Attributes_AttackPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.AttackPower"));
	GameplayTags.Attributes_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.AttackSpeed"));
	GameplayTags.Attributes_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.MoveSpeed"));

	GameplayTags.Attributes_Resistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance"));
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"));
	GameplayTags.Attributes_Resistance_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lighting"));
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"));

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"));
	GameplayTags.Damage_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lighting"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"));

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lighting, GameplayTags.Attributes_Resistance_Lighting);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"));

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"));

	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.Weapon"));
	GameplayTags.Montage_Attack_UnarmedRight = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.UnarmedRight"));
	GameplayTags.Montage_Attack_UnarmedLeft = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.UnarmedLeft"));
}
