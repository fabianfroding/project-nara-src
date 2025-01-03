// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "UI/NaraUserWidget.h"

#include "NaraPlayerHealthWidget.generated.h"

UCLASS()
class NARA_API UNaraPlayerHealthWidget : public UNaraUserWidget
{
	GENERATED_BODY()

private:
	const class UNaraAttributeSet* CachedAttributeSet;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ContainerIconClass;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	UUniformGridPanel* GetHealthIconContainer();
	virtual UUniformGridPanel* GetHealthIconContainer_Implementation();
	
	UFUNCTION(BlueprintCallable)
	void HandleHealthChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintCallable)
	void HandleMaxHealthChanged(float OldValue, float NewValue);

};
