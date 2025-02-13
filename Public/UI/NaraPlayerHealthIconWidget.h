// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "NaraPlayerHealthIconWidget.generated.h"

UCLASS()
class NARA_API UNaraPlayerHealthIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateIconState(const bool bIsFilled);
	virtual void UpdateIconState_Implementation(const bool bIsFilled);
	
};
