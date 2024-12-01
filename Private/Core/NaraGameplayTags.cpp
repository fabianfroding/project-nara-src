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
}
