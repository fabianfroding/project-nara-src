// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraGameplayAbility.h"

#include "NaraProjectileAbility.generated.h"

class ANaraProjectile;
class UGameplayEffect;

UCLASS()
class NARA_API UNaraProjectileAbility : public UNaraGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ANaraProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

};
