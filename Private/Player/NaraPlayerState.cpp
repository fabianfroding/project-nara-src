// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Player/NaraPlayerState.h"

#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"

ANaraPlayerState::ANaraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UNaraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UNaraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ANaraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
