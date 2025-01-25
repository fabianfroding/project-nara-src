// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraProjectileAbility.h"

#include "PlayerAttackAbility.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UGameplayEffect;

/* TODO: This ability currently does not block jump, dash etc. Using Player.Block.InputPressed in ActivationOwnedTags also blocks rotation, 
	which we still want while this ability is active. So we need an input blocker tag that disabled input pressed but not rotation.
*/
UCLASS()
class NARA_API UPlayerAttackAbility : public UNaraProjectileAbility
{
	GENERATED_BODY()

private:
	//float StartTime = 0.f; // In case we want to allow player to charge up the ability.

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
