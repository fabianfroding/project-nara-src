// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "NaraAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;

UCLASS()
class NARA_API UNaraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
};
