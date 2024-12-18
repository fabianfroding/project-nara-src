// Copyright Fabian Fröding 2024. All Right Reserved.

#include "GASCalculations/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "Core/NaraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GAS/NaraAttributeSet.h"
#include "Libraries/NaraAbilitySystemLibrary.h"

struct NaraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Tenacity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;

	NaraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UNaraAttributeSet, Tenacity, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UNaraAttributeSet, FireResistance, Target, false);

		TagsToCaptureDefs.Add(FNaraGameplayTags::Get().Attributes_Tenacity, TenacityDef);
		TagsToCaptureDefs.Add(FNaraGameplayTags::Get().Attributes_Resistance_Fire, FireResistanceDef);
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
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
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
	float Damage = 0.f;
	for (const TPair<FGameplayTag, FGameplayTag>& Pair : FNaraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		if (!NaraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag))
			continue;
		//checkf(NaraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), 
			//TEXT("UExecCalc_Damage::Execute_Implementation: TagsToCaptureDefs doesnt contain %s"), *ResistanceTag.ToString());

		const FGameplayEffectAttributeCaptureDefinition CaptureDef = NaraDamageStatics().TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParams, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;

		Damage += DamageTypeValue;
	}

	// Capture block chance on target and determine if there was a succesful block
	// If block, halve damage. (Using Tenacity here for testing purposes, since we are not going to have complex attribute calulations later on).
	float TargetBlockChance = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().TenacityDef, EvaluationParams, TargetBlockChance);
	//TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UNaraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

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
