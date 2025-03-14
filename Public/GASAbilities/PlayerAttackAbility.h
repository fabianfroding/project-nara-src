// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraProjectileAbility.h"

#include "PlayerAttackAbility.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UGameplayEffect;

UCLASS()
class NARA_API UPlayerAttackAbility : public UNaraProjectileAbility
{
	GENERATED_BODY()

private:
	bool bHasProjectileReturned = true;

	UPROPERTY()
	UAbilitySystemComponent* CachedASC;

	UPROPERTY()
	FActiveGameplayEffectHandle AttackActiveEffectHandle;

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag EventAttackMontageTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag SpawnProjectileSocketTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PlayerAttackEndTag;

	// Gameplay effect applied to the player from activation until montage end/projectile fired.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> AttackActiveEffectClass;

	/* Using the default "BlockAbilitiesWithTag" will not suffice for this ability since it ends when the projectile has returned,
	 * and we don't want to block any abilities after the projectile has spawned.
	*/

	// Abilities blocked while activating the ability until the projectile has spawned.
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer CustomBlockedAbilityTags;

public:
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

private:
	UFUNCTION()
	void RestoreMovement();

	UFUNCTION()
	void OnGameplayEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void OnPlayerAttackEnd(FGameplayEventData Payload);

};
