// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraGameplayAbility.h"

#include "NaraSummonAbility.generated.h"

UCLASS()
class NARA_API UNaraSummonAbility : public UNaraGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 NumMinions = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnSpread = 90.f;
	
public:
	UFUNCTION(BlueprintPure)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure)
	TSubclassOf<APawn> GetRandomMinionClass();
};
