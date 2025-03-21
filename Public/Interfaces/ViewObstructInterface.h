// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "ViewObstructInterface.generated.h"

UINTERFACE(MinimalAPI)
class UViewObstructInterface : public UInterface
{
	GENERATED_BODY()
};

class NARA_API IViewObstructInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ViewObstructed(AActor* ObstructedActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ViewObstructedEnd(AActor* ObstructedActor);

};
