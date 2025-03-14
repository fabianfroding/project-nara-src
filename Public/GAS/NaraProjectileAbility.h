// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraDamageGameplayAbility.h"

#include "NaraProjectileAbility.generated.h"

class ANaraProjectile;
class UGameplayEffect;
struct FGameplayTag;

UCLASS()
class NARA_API UNaraProjectileAbility : public UNaraDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ANaraProjectile> ProjectileClass;
	
protected:
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);

};
