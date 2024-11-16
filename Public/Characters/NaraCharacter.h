// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "Characters/NaraCharacterBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "NaraCharacter.generated.h"

class UNaraHealthComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ANaraCharacter : public ANaraCharacterBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNaraHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	class UNaraFlashComponent* FlashComponent;

	/* GAS Variables */
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	const class UNaraMovementSet* MovementAttributeSet;
	/* End GAS Variables */

public:
	ANaraCharacter();

};

