// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/LoadScreenWidget.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	/*LoadScreenWidget = CreateWidget<ULoadScreenWidget>(GetWorld(), LoadScreenWidgetClass);
	LoadScreenWidget->AddToViewport();
	LoadScreenWidget->BlueprintInitializeWidget();*/
}
