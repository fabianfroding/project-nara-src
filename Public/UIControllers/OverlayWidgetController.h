// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "UIControllers/NaraWidgetController.h"

#include "OverlayWidgetController.generated.h"

class UNaraUserWidget;
class UNaraAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

UCLASS()
class NARA_API UOverlayWidgetController : public UNaraWidgetController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxManaChanged;

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

protected:
	void ManaChanged(const FOnAttributeChangeData& Data) const { OnManaChanged.Broadcast(Data.NewValue); }
	void MaxManaChanged(const FOnAttributeChangeData& Data) const { OnMaxManaChanged.Broadcast(Data.NewValue); }

	// TODO: Move this to a function library instead.
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag);
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag)
{
	return Table->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
