// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraGameplayAbility.h"
#include "Interfaces/CombatInterface.h"
#include "Types/NaraAbilityTypes.h"

#include "NaraDamageGameplayAbility.generated.h"

UCLASS()
class NARA_API UNaraDamageGameplayAbility : public UNaraGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly)
	float DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float DebuffDuration = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float KnockbackForceMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float KnockbackChance = 0.f;

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(
		AActor* TargetActor = nullptr,
		bool bOverrideKnockbackDirection = false,
		FVector KnockbackDirectionOverride = FVector::ZeroVector,
		bool bOverridePitch = false,
		float PitchOverride = 0.f) const;

protected:
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages);

};
