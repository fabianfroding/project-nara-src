// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "NaraAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class UOverlayWidgetController;

UCLASS()
class NARA_API UNaraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable)
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintPure)
	static bool IsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable)
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintPure)
	static bool IsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable)
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	/* Debuff Utility Functions */
	UFUNCTION(BlueprintPure)
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure)
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure)
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure)
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure)
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable)
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInSuccessfulDebuff);

	UFUNCTION(BlueprintCallable)
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDamage);

	UFUNCTION(BlueprintCallable)
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDuration);

	UFUNCTION(BlueprintCallable)
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InFrequency);

	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);
	/* End Debuff Utility Functions */

	UFUNCTION(BlueprintPure)
	static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable)
	static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);

	UFUNCTION(BlueprintCallable)
	static void GetAlivePlayersInRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, 
		const TArray<AActor*> ActorsToIgnore, const float Radius, const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure)
	static bool AreActorsEnemies(const AActor* ActorA, const AActor* ActorB);

	UFUNCTION(BlueprintCallable)
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

	UFUNCTION(BlueprintPure)
	static TArray<FRotator> EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);

	UFUNCTION(BlueprintPure)
	static TArray<FVector> EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors);

	static void DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec,
		FAggregatorEvaluateParameters EvaluationParameters, const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs);
};
