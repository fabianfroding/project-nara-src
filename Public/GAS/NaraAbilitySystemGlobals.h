// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"

#include "NaraAbilitySystemGlobals.generated.h"

UCLASS()
class NARA_API UNaraAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
