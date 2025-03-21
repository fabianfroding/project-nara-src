// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/NaraProjectile.h"

#include "NaraReturningProjectile.generated.h"

class USoundBase;
class UTimelineComponent;

UCLASS()
class NARA_API ANaraReturningProjectile : public ANaraProjectile
{
	GENERATED_BODY()

private:
	FVector InitialLocation;
	FVector TargetLocation;
	TObjectPtr<AActor> ReturnToActor;

protected:
	UPROPERTY(EditDefaultsOnly)
	float TravelDistance = 600.f;

	// How close the projectile has to be to it's returning destination to trigger impact.
	UPROPERTY(EditDefaultsOnly)
	float ReturnImpactDistance = 80.f;

	// Allows the projectile to home back to the instigator instead of it's initial location.
	UPROPERTY(EditDefaultsOnly)
	bool ReturnToInstigator = false;

	// Allows the projectile to damage the same target both on the way out and back.
	UPROPERTY(EditDefaultsOnly)
	bool bResetTargetsOnReturn = true;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ReturnSFX;

	// Used to execute gameplay cue when projectile finished return.
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ReturnedCueTag;
	
public:
	ANaraReturningProjectile();

	void SetReturnToTarget(AActor* TargetActor) { ReturnToActor = TargetActor; }

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UTimelineComponent* GetOutgoingTimeline() const;
	virtual UTimelineComponent* GetOutgoingTimeline_Implementation() const { return nullptr; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UTimelineComponent* GetReturningTimeline() const;
	virtual UTimelineComponent* GetReturningTimeline_Implementation() const { return nullptr; }

	UFUNCTION(BlueprintCallable)
	void OutgoingUpdate(const float Delta);

	UFUNCTION(BlueprintCallable)
	void OutgoingFinish();

	UFUNCTION(BlueprintCallable)
	void ReturningUpdate(const float Delta);

};
