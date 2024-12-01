// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameplayTags.h"

#include "GameplayTagsManager.h"

FNaraGameplayTags FNaraGameplayTags::GameplayTags;

void FNaraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Armor"), FString("Reduces damage taken."));
}
