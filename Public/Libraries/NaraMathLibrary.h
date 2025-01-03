// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "NaraMathLibrary.generated.h"

UCLASS()
class NARA_API UNaraMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static FVector GetPointWithPolarOffset(FVector Origin, float Distance, float Angle);

};
