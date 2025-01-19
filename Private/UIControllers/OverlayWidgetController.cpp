// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UIControllers/OverlayWidgetController.h"

#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UNaraAttributeSet* NaraAttributeSet = Cast<UNaraAttributeSet>(AS);
	OnManaChanged.Broadcast(NaraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(NaraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UNaraAttributeSet* NaraAttributeSet = CastChecked<UNaraAttributeSet>(AS);
	ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(NaraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}
