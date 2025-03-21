// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"

#include "NaraCommonRootWidget.generated.h"

class UCommonActivatableWidget;
class UCommonActivatableWidgetStack;

/** NaraCommonRootWidget
 * Widget used a root of a widget stack.
 */

UCLASS()
class NARA_API UNaraCommonRootWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	void ClearWidgetStack();
	UCommonActivatableWidget* PushWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	void PopWidget(UCommonActivatableWidget* ActivatableWidget);
	
protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	UCommonActivatableWidgetStack* GetWidgetStack();

};
