// Copyright Fabian Fröding 2025. All Right Reserved.

#include "UI/NaraCommonRootWidget.h"

#include "CommonActivatableWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UNaraCommonRootWidget::ClearWidgetStack()
{
	UCommonActivatableWidgetStack* WidgetStack = GetWidgetStack();
	if (!WidgetStack)
		return;

	TArray<UCommonActivatableWidget*> WidgetStackList = WidgetStack->GetWidgetList();

	for (int32 i = WidgetStack->GetWidgetList().Num() - 1; i >= 0; i--)
	{
		if (UCommonActivatableWidget* ActivatableWidget = Cast<UCommonActivatableWidget>(WidgetStack->GetWidgetList()[i]))
		{
			//ActivatableWidget->OnWidgetPopped();
			WidgetStack->RemoveWidget(*ActivatableWidget);

			// If no active widget in stack hides HUD after popping, then restore HUD visibility.
			for (UCommonActivatableWidget* Widget : WidgetStackList)
			{
				if (!Widget->IsActivated())
					continue;

				/*if (UNaraCommonActivatableWidget* NaraCommonActivatableWidget = Cast<UNaraCommonActivatableWidget>(Widget))
				{
					if (UNaraCommonActivatableWidget->bHidesHUD)
						return;
				}*/
			}

			APlayerController* PlayerController = GetOwningPlayer();
			PlayerController->SetInputMode(FInputModeGameOnly());

			/*if (ANaraPlayerController* NaraPlayerController = Cast<ANaraPlayerController>(PlayerController))
				NaraPlayerController->ShowGameOverlay();*/
		}
	}
}

UCommonActivatableWidget* UNaraCommonRootWidget::PushWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!UKismetSystemLibrary::IsValidClass(ActivatableWidgetClass))
		return nullptr;

	UCommonActivatableWidgetStack* WidgetStack = GetWidgetStack();
	if (!WidgetStack)
		return nullptr;

	if (UCommonActivatableWidget* PushedWidget = Cast<UCommonActivatableWidget>(WidgetStack->AddWidget(ActivatableWidgetClass)))
	{
		/*if (PushedWidget->bHidesHUD)
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayer()))
				PlayerController->HideGameHUD();
		}*/
		return PushedWidget;
	}
	return nullptr;
}

void UNaraCommonRootWidget::PopWidget(UCommonActivatableWidget* ActivatableWidget)
{
	if (!ActivatableWidget)
		return;

	UCommonActivatableWidgetStack* WidgetStack = GetWidgetStack();
	if (!WidgetStack)
		return;

	//ActivatableWidget->OnWidgetPopped();
	WidgetStack->RemoveWidget(*ActivatableWidget);

	// If no active widget in stack hides HUD after popping, then restore HUD visibility.
	for (UCommonActivatableWidget* Widget : WidgetStack->GetWidgetList())
	{
		if (!Widget->IsActivated())
			continue;
		/*if (UNaraCommonActivatableWidget* NaraCommonActivatableWidget = Cast<UNaraCommonActivatableWidget>(Widget))
		{
			if (NaraCommonActivatableWidget->bHidesHUD)
				return;
		}*/
	}

	APlayerController* PlayerController = GetOwningPlayer();
	PlayerController->SetInputMode(FInputModeGameOnly());

	/*if (ANaraPlayerController* NaraPlayerController = Cast<ANaraPlayerController>(PlayerController))
		NaraPlayerController->ShowGameHUD();*/
}
