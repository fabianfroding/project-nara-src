// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NaraCharacterBase.h"

#include "NaraPlayerCharacter.generated.h"

class UCameraComponent;
class UGameplayAbility;
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

	UPROPERTY()
	FOnPlayerInitAbilityActorInfo OnPlayerInitAbilityActorInfo;

public:
	ANaraPlayerCharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SaveProgress(const FName& CheckpointTag);

	/* Combat Interface Functions */
	virtual void Die() override { OnPlayerDie(); }
	virtual bool IsDead_Implementation() const override;
	/* End Combat Interface Functions */

protected:
	virtual void InitAbilityActorInfo() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerDie();
	
};
