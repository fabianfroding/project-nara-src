// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "UI/NaraUserWidget.h"

#include "NaraPlayerHealthWidget.generated.h"

class UNaraHealthComponent;

UCLASS()
class NARA_API UNaraPlayerHealthWidget : public UNaraUserWidget
{
	GENERATED_BODY()

private:
	// TODO: It shouldnt have any references, data should be broadcasted via delegates only.
	UNaraHealthComponent* CachedHealthComponent;
	const class UNaraHealthSet* CachedHealthSet;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ContainerIconClass;

protected:
	virtual void NativeOnInitialized() override;
	
	// Temporary solution.
	UFUNCTION(BlueprintCallable)
	void ForceInitialize();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	UUniformGridPanel* GetHealthIconContainer();
	virtual UUniformGridPanel* GetHealthIconContainer_Implementation();
	
private:
	UFUNCTION()
	void HandleHealthChanged(UNaraHealthComponent* HealthComponent, float OldValue, float NewValue);

	UFUNCTION()
	void HandleMaxHealthChanged(UNaraHealthComponent* HealthComponent, float OldValue, float NewValue);

};
