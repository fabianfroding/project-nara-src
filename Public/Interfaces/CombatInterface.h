// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CombatInterface.generated.h"

class UAnimMontage;

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class NARA_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual FVector GetCombatSocketLocation();

	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();
};
