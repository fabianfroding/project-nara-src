// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/NaraProjectile.h"

#include "NaraBoomerangProjectile.generated.h"

class USkeletalMeshComponent;
class USoundBase;

UCLASS()
class NARA_API ANaraBoomerangProjectile : public ANaraProjectile
{
	GENERATED_BODY()

private:
	float DefaultSpeed = 0.f;
	float ElapsedTime = 0.f;
	float ClampedDestinationSpeedModifier = 1.f;
	float ClampedReturnSpeedModifier = 1.f;
	USkeletalMeshComponent* CachedInstigatorMesh;

protected:
	UPROPERTY(EditDefaultsOnly)
	float TimeUntilReturn = 1.f; // TODO: It might be easier to control this by distance rather than time.

	// By how much the projectile should slow down the closer it is to its destination/end point. Clamped between 0-1;
	UPROPERTY(EditDefaultsOnly)
	float DestinationSpeedModifier = 0.f;

	// If the return speed should be faster/slower. Negatives values clamped to 0.
	UPROPERTY(EditDefaultsOnly)
	float ReturnSpeedModifier = 1.f;

	// Allows the projectile to damage the same target both on the way out and back.
	UPROPERTY(EditDefaultsOnly)
	bool bResetTargetsOnReturn = true;

	// Tag used to execute gameplay cue when projectile returned to owner.
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ReturnedToOwnerTag;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ReturnSFX;

	// Name of the socket 
	UPROPERTY(EditDefaultsOnly)
	FName ReturnMeshSocketName;

public:
	ANaraBoomerangProjectile();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	bool IsReturning() const { return ElapsedTime >= TimeUntilReturn; }

private:
	void ReturnToInstigator();

};
