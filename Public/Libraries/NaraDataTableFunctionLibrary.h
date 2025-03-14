// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "NaraDataTableFunctionLibrary.generated.h"

UCLASS()
class NARA_API UNaraDataTableFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag);

};

template<typename T>
inline T* UNaraDataTableFunctionLibrary::GetDataTableRowByTag(UDataTable* Table, const FGameplayTag& Tag)
{
	return Table->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
