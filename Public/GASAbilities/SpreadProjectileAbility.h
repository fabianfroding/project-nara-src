// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraProjectileAbility.h"

#include "SpreadProjectileAbility.generated.h"

UCLASS()
class NARA_API USpreadProjectileAbility : public UNaraProjectileAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpread = 90.f;

	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;

	UPROPERTY(EditDefaultsOnly)
	float HomingAccelerationMin = 1600.f;

	UPROPERTY(EditDefaultsOnly)
	float HomingAccelerationMax = 3200.f;

	UPROPERTY(EditDefaultsOnly)
	bool bLaunchHomingProjectiles = true;

public:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget);

};
