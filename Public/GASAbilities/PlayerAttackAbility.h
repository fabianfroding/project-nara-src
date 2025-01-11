// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraProjectileAbility.h"

#include "PlayerAttackAbility.generated.h"

class UAnimMontage;

/* TODO: This ability currently does not block jump, dash etc.Using Player.Block.InputPressed in ActivationOwnedTags also blocks rotation, 
	which we still want while this ability is active. So we need an input blocker tag that disabled input pressed but not rotation.
*/
UCLASS()
class NARA_API UPlayerAttackAbility : public UNaraProjectileAbility
{
	GENERATED_BODY()

private:
	float DefaultMoveSpeed = 0.f;

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag EventAttackMontageTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag SpawnProjectileSocketTag;
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

private:
	UFUNCTION()
	void RestoreMovement();

	UFUNCTION()
	void OnInputReleased(float TimeHeld);

	UFUNCTION()
	void OnGameplayEventReceived(FGameplayEventData Payload);

};
