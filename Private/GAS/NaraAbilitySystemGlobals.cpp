// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GAS/NaraAbilitySystemGlobals.h"

#include "Types/NaraAbilityTypes.h"

FGameplayEffectContext* UNaraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FNaraGameplayEffectContext();
}
