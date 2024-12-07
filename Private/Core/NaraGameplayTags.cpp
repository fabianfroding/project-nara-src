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

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"));
}
