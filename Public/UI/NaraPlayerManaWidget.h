// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UI/NaraUserWidget.h"

#include "NaraPlayerManaWidget.generated.h"

class UAbilitySystemComponent;

UCLASS()
class NARA_API UNaraPlayerManaWidget : public UNaraUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void BindCallbacksToDependencies(UAbilitySystemComponent* ASC) override;

protected:
	virtual void NativeOnInitialized() override;

	void HandleManaChanged(const FOnAttributeChangeData& Data) { ManaChanged(Data.OldValue, Data.NewValue); }

	UFUNCTION(BlueprintImplementableEvent)
	void ManaChanged(const float OldValue, const float NewValue);

};
