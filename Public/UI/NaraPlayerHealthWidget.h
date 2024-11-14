// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"

#include "NaraPlayerHealthWidget.generated.h"

UCLASS()
class NARA_API UNaraPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	class UNaraHealthComponent* CachedHealthComponent;
	const class UNaraHealthSet* CachedHealthSet;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ContainerIconClass;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	UUniformGridPanel* GetHealthIconContainer();
	virtual UUniformGridPanel* GetHealthIconContainer_Implementation();
	
private:
	UFUNCTION()
	void UpdateHealthDisplay();

};
