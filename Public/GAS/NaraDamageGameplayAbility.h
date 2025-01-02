// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraGameplayAbility.h"
#include "Interfaces/CombatInterface.h"

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

	UPROPERTY(EditDefaultsOnly)
	FScalableFloat Damage;

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

protected:
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages);

};
