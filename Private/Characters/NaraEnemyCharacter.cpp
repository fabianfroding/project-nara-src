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
		// NOTE: For some reason we can't use FOnAttributeChangeData in header files, 
		// so we need to use a lambda here in the .cpp instead of definiing and using a function in the header file.
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NaraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		
	}
}

void ANaraEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UNaraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}
