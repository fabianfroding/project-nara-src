// Copyright Fabian Fröding 2025. All Right Reserved.

#include "UI/NaraPlayerManaWidget.h"

#include "AbilitySystemComponent.h"
#include "Characters/NaraPlayerCharacter.h"
#include "GAS/NaraAttributeSet.h"

void UNaraPlayerManaWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ANaraPlayerCharacter* NaraPlayerCharacter = Cast<ANaraPlayerCharacter>(GetOwningPlayerPawn()))
		NaraPlayerCharacter->OnPlayerInitAbilityActorInfo.AddUniqueDynamic(this, &UNaraPlayerManaWidget::BindCallbacksToDependencies);
}

void UNaraPlayerManaWidget::BindCallbacksToDependencies(UAbilitySystemComponent* ASC)
{
	if (!ASC)
		return;

	if (const UNaraAttributeSet* NaraAttributeSet = Cast<UNaraAttributeSet>(ASC->GetAttributeSet(UNaraAttributeSet::StaticClass())))
		ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetManaAttribute()).AddUObject(this, &UNaraPlayerManaWidget::HandleManaChanged);
}
