// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "NaraPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UNaraAbilitySystemComponent;
class UNaraInputConfig;
struct FInputActionValue;

UCLASS()
class NARA_API ANaraPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UNaraAbilitySystemComponent> NaraASC;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> NaraContext;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNaraInputConfig> InputConfig;

public:
	UNaraAbilitySystemComponent* GetASC();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
};
