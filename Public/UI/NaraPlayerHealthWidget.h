// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "GameplayEffectTypes.h"
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

public:
	UFUNCTION()
	virtual void BindCallbacksToDependencies(UAbilitySystemComponent* ASC) override;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	UUniformGridPanel* GetHealthIconContainer();
	virtual UUniformGridPanel* GetHealthIconContainer_Implementation();

	void HealthChanged(const FOnAttributeChangeData& Data) { HandleHealthChanged(Data.OldValue, Data.NewValue); }
	void MaxHealthChanged(const FOnAttributeChangeData& Data) { HandleMaxHealthChanged(Data.OldValue, Data.NewValue); }
	
	UFUNCTION()
	void HandleHealthChanged(float OldValue, float NewValue);

	UFUNCTION()
	void HandleMaxHealthChanged(float OldValue, float NewValue);

};
