// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraEnemyCharacter.h"

#include "GAS/NaraAbilitySystemComponent.h"
#include "GASAttributeSets/NaraAttributeSet.h"

ANaraEnemyCharacter::ANaraEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UNaraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UNaraAttributeSet>("AttributeSet");
}

void ANaraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
