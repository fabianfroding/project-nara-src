// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UIControllers/NaraWidgetController.h"

void UNaraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	ASC = WCParams.AbilitySystemComponent;
	AS = WCParams.AttributeSet;
}

void UNaraWidgetController::BroadcastInitialValues() {}

void UNaraWidgetController::BindCallbacksToDependencies() {}
