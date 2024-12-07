// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Characters/NaraEnemyCharacter.h"

#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"

ANaraEnemyCharacter::ANaraEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UNaraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UNaraAttributeSet>("AttributeSet");
}

void ANaraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	UNaraAttributeSet* NaraAS = CastChecked<UNaraAttributeSet>(AttributeSet);
	if (NaraAS)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NaraAS->GetHealthAttribute()).AddUObject(this, &ANaraEnemyCharacter::BroadcastHealthChanged);
		OnHealthChanged.Broadcast(NaraAS->GetHealth());
	}
}

void ANaraEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UNaraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}

void ANaraEnemyCharacter::BroadcastHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}
