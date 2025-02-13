// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "NaraGameplayAbility.generated.h"

class AAreaIndicator;

UCLASS()
class NARA_API UNaraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	float StartTime = 0.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ActivationSFX;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAreaIndicator> AreaIndicatorClass;

	UPROPERTY()
	TObjectPtr<AAreaIndicator> AreaIndicator;
	
public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag StartupInputTag;

public:
	UFUNCTION(BlueprintCallable)
	void ShowAreaIndicator(UMaterialInterface* DecalMaterial = nullptr);

	UFUNCTION(BlueprintCallable)
	void HideAreaIndicator();

	UFUNCTION(BlueprintCallable)
	void UpdateAreaIndicatorLocation(const FVector& NewLocation);

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

};
