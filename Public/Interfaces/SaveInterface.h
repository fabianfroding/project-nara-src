// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SaveInterface.generated.h"

UINTERFACE(MinimalAPI)
class USaveInterface : public UInterface
{
	GENERATED_BODY()
};

class NARA_API ISaveInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ShouldLoadTransform();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LoadActor();

};
