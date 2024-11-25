// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "UIControllers/NaraWidgetController.h"

#include "OverlayWidgetController.generated.h"

class UNaraUserWidget;

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

UCLASS()
class NARA_API UOverlayWidgetController : public UNaraWidgetController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> MessageWidgetDataTable;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMaxManaChangedSignature OnMaxManaChanged;

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag);
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
