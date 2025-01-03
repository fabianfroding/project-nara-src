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
struct FNaraAbilityInfo;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UNaraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWidgetMessageRowSignature, FUIWidgetRow, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FNaraAbilityInfo&, Info);

UCLASS()
class NARA_API UOverlayWidgetController : public UNaraWidgetController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageWidgetDataTable;

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable)
	FWidgetMessageRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable)
	FAbilityInfoSignature AbilityInfoDelegate;

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const { OnHealthChanged.Broadcast(Data.NewValue); }
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const { OnMaxHealthChanged.Broadcast(Data.NewValue); }
	void ManaChanged(const FOnAttributeChangeData& Data) const { OnManaChanged.Broadcast(Data.NewValue); }
	void MaxManaChanged(const FOnAttributeChangeData& Data) const { OnMaxManaChanged.Broadcast(Data.NewValue); }

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag);

	void OnInitializeStartupAbilities(UNaraAbilitySystemComponent* NaraAbilitySystemComponent);
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag)
{
	return Table->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
