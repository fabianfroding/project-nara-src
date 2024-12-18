// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"

#include "MMC_SampleCalc.generated.h"

// NOTE: MMC stands for modifier magnitude calculation.
// This sample shows have the health attribute can be calculated based on...

UCLASS()
class NARA_API UMMC_SampleCalc : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_SampleCalc();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition AttackPowerDef;

};
