// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NaraCharacter.h"

#include "NaraPlayerCharacter.generated.h"

class UCameraComponent;
class UGameplayAbility;
class USpringArmComponent;

UCLASS()
class NARA_API ANaraPlayerCharacter : public ANaraCharacter
{
	GENERATED_BODY()

protected:
	/* GAS Variables */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TArray<TSoftClassPtr<UGameplayAbility>> StartingAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSoftClassPtr<UGameplayAbility> PlayerBoomerangAbility;
	/* End GAS Variables */

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	ANaraPlayerCharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void InitAbilityActorInfo() override;
	
};
