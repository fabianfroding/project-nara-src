// Copyright Fabian Fr�ding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NaraCharacterBase.h"

#include "NaraPlayerCharacter.generated.h"

class UCameraComponent;
class UGameplayAbility;
class UGameplayEffect;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInitAbilityActorInfo, UAbilitySystemComponent*, ASC);

UCLASS()
class NARA_API ANaraPlayerCharacter : public ANaraCharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultsAttributesSetByCaller;

	UPROPERTY(EditDefaultsOnly)
	float DeathTime = 5.f;

	FTimerHandle DeathTimer;

	UPROPERTY()
	FOnPlayerInitAbilityActorInfo OnPlayerInitAbilityActorInfo;

public:
	ANaraPlayerCharacter();

	virtual void AddCharacterAbilities() override;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SaveProgress(const FName& CheckpointTag);
	void LoadProgress();

	/* Combat Interface Functions */
	virtual void Die() override;
	virtual bool IsDead_Implementation() const override;
	/* End Combat Interface Functions */

protected:
	virtual void InitAbilityActorInfo() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDie();
	
};
