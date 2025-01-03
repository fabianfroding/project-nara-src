// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "NaraGameplayAbility.generated.h"

UCLASS()
class NARA_API UNaraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag StartupInputTag;

};
