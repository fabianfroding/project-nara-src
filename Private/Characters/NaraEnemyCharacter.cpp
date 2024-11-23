// Copyright Fabian Fr�ding 2024. All Right Reserved.

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
	InitAbilityActorInfo();
}

void ANaraEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UNaraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
