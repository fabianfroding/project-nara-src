// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/NaraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/NaraUserWidget.h"

void ANaraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
