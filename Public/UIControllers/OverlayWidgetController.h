// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UIControllers/NaraWidgetController.h"

#include "OverlayWidgetController.generated.h"

UCLASS()
class NARA_API UOverlayWidgetController : public UNaraWidgetController
{
	GENERATED_BODY()

protected:
	// TODO: Move this to a function library instead.
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag);
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag)
{
	return Table->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
