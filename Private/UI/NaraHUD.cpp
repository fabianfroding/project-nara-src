// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/NaraHUD.h"

#include "CommonActivatableWidget.h"

ANaraHUD* ANaraHUD::GetNaraHUD(APlayerController* PlayerController)
{
	if (!PlayerController)
		return nullptr;

	return Cast<ANaraHUD>(PlayerController->GetHUD());
}

void ANaraHUD::PushWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, UCommonActivatableWidget*& OutWidget, APlayerController* PlayerController)
{
	if (!PlayerController)
		return;

	/*if (ANaraPlayerController* PlayerController = Cast<ANaraPlayerController>(PlayerController))
	{
		if (UNaraCommonRootWidget* NaraCommonRootWidget = PlayerController->GetNaraRootWidget())
		{
			OutWidget = NaraCommonRootWidget->PushWidget(ActivatableWidgetClass);
			if (ANaraHUD* NaraHUD = ANaraHUD::GetNaraHUD(PlayerController))
				NaraHUD->OnWidgetPushed.Broadcast(OutWidget);
		}
	}*/
}

void ANaraHUD::PopWidget(UCommonActivatableWidget* ActivatableWidget)
{
	if (!ActivatableWidget)
		return;

	/*if (APlayerController* PlayerController = Cast<APlayerController>(ActivatableWidget->GetOwningPlayer()))
	{
		if (UNaraCommonRootWidget* NaraCommonRootWidget = RPlayerController->GetNaraRootWidget())
		{
			ANaraHUD->PopWidget(ActivatableWidget);
			if (ANaraHUD* NaraHUD = ANaraHUD::GetNaraHUD(RPlayerController))
				NaraHUD->OnWidgetPopped.Broadcast(ActivatableWidget);
		}
	}*/
}
