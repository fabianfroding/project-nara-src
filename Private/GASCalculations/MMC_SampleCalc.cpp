// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASCalculations/MMC_SampleCalc.h"

#include "GAS/NaraAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_SampleCalc::UMMC_SampleCalc()
{
	AttackPowerDef.AttributeToCapture = UNaraAttributeSet::GetAttackPowerAttribute();
	AttackPowerDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AttackPowerDef.bSnapshot = false; // When do we want to capture the attribute? On created or applied? Snapshot captures it immediately.

	RelevantAttributesToCapture.Add(AttackPowerDef);
}

float UMMC_SampleCalc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target.
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float AttackPower = 0.f;
	GetCapturedAttributeMagnitude(AttackPowerDef, Spec, EvaluationParameters, AttackPower);
	AttackPower = FMath::Max<float>(0.f, AttackPower);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	// const int32 Level = CombatInterface->GetLevel(); // EXAMPLE.

	return 80.f + (2.5f * AttackPower) + (10.f /** Level*/);
}
