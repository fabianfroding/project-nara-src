// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UIControllers/NaraWidgetController.h"

#include "Player/NaraPlayerController.h"
#include "Player/NaraPlayerState.h"
#include "GAS/NaraAbilitySystemComponent.h"
#include "GAS/NaraAttributeSet.h"

void UNaraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	ASC = WCParams.AbilitySystemComponent;
	AS = WCParams.AttributeSet;
}

void UNaraWidgetController::BroadcastInitialValues() {}

void UNaraWidgetController::BindCallbacksToDependencies() {}

ANaraPlayerController* UNaraWidgetController::GetNaraPlayerController() const
{
	return Cast<ANaraPlayerController>(PlayerController);
}

ANaraPlayerState* UNaraWidgetController::GetNaraPlayerState() const
{
	return Cast<ANaraPlayerState>(PlayerState);
}

UNaraAbilitySystemComponent* UNaraWidgetController::GetNaraASC() const
{
	return Cast<UNaraAbilitySystemComponent>(ASC);
}

UNaraAttributeSet* UNaraWidgetController::GetNaraAttributeSet() const
{
	return Cast<UNaraAttributeSet>(AS);
}
