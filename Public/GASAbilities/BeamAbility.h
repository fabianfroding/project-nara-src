// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GAS/NaraDamageGameplayAbility.h"

#include "BeamAbility.generated.h"

UCLASS()
class NARA_API UBeamAbility : public UNaraDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	FVector HitLocation;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> HitActor;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> OwnerPlayerController;


	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ACharacter> OwnerCharacter;

public:
	UFUNCTION(BlueprintCallable)
	void StoreHitDataInfo(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariables();

};
