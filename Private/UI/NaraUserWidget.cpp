// Copyright Fabian Fröding 2024. All Right Reserved.

#include "UI/NaraUserWidget.h"

void UNaraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
