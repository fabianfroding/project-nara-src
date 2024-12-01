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
	FGameplayTag Attributes_Armor;

public:
	static const FNaraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
};