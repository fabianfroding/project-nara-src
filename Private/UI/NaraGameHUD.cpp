// Copyright Fabian Fröding 2025. All Right Reserved.

#include "UI/NaraGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/NaraUserWidget.h"

void ANaraGameHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninitialized!"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UNaraUserWidget>(Widget);
	OverlayWidget->SetWidgetController();

	Widget->AddToViewport();
}
