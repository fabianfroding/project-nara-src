// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraDamageGameplayAbility.h"

#include "NaraFireBlast.generated.h"

class ANaraProjectile;

UCLASS()
class NARA_API UNaraFireBlast : public UNaraDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 NumFireBalls = 12;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ANaraProjectile> ProjectileClass;

protected:
	UFUNCTION(BlueprintCallable)
	TArray<ANaraProjectile*> SpawnProjectiles();

};
