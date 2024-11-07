// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "NaraCharacter.generated.h"

class UAbilitySystemComponent;
class UNaraHealthComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ANaraCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNaraHealthComponent* HealthComponent;

	/* GAS Variables */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;
	/* End GAS Variables */

public:
	ANaraCharacter();
	
	UNaraHealthComponent* GetHealthComponent() const { return HealthComponent; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

private:
	UFUNCTION()
	void OnAbilitySystemComponentInitialized(UActorComponent* Component, bool bReset);

};

