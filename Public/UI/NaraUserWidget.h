// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "NaraUserWidget.generated.h"

class UAbilitySystemComponent;

UCLASS()
class NARA_API UNaraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController();

	virtual void BindCallbacksToDependencies(UAbilitySystemComponent* ASC) {}

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
