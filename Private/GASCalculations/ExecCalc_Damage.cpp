// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASCalculations/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "Core/NaraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GAS/NaraAttributeSet.h"

struct NaraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Tenacity);

	NaraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UNaraAttributeSet, Tenacity, Target, false);
	}
};

static const NaraDamageStatics& DamageStatics()
{
	// A static variable inside a static functions doesn't go away, even though it's not dynamically allocated on the heap.
	static NaraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().TenacityDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	// Get damage set by caller magnitude.
	float Damage = Spec.GetSetByCallerMagnitude(FNaraGameplayTags::Get().Damage);

	// Capture block chance on target and determine if there was a succesful block
	// If block, halve damage. (Using Tenacity here for testing purposes, since we are not going to have complex attribute calulations later on).
	//float TargetBlockChance = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().TenacityDef, EvaluationParams, TargetBlockChance);
	//TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	//const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	//Damage = bBlocked ? 0.f : Damage;

	// Here we can capture additional attributes such as: TargetArmor, SourceArmorPenetration etc.

	//float Tenacity = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().TenacityDef, EvaluationParams, Tenacity);
	//Tenacity = FMath::Max<float>(0.f, Tenacity);
	
	// This is additively increasing the tenacity of the target.
	//++Tenacity; // Sample calc. This is where comlicated calculations are done.

	//const FGameplayModifierEvaluatedData EvaluatedData(DamageStatics().TenacityProperty, EGameplayModOp::Additive, Tenacity);

	const FGameplayModifierEvaluatedData EvaluatedData(UNaraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
