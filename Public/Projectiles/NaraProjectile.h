// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Types/NaraAbilityTypes.h"

#include "NaraProjectile.generated.h"

// TODO: Consider adding a NaraEffectActor base class for objects that apply effects.
// This can then be a subclass of that actor with a projectile movement component.
// The base class can then also function as pickups.

class UGameplayEffect;
class UNiagaraSystem;
class UProjectileMovementComponent;
class USoundBase;
class USphereComponent;

UCLASS()
class NARA_API ANaraProjectile : public AActor
{
	GENERATED_BODY()

private:
	bool bHit = false;

	TArray<AActor*> HitActors;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag InstantGameplayEffectMagnitudeTag;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactVFX;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSFX;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSFX;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSFXComponent;

	UPROPERTY(EditDefaultsOnly)
	bool bIgnoreInstigator = true;

	UPROPERTY(EditDefaultsOnly)
	bool bDontDestroyOnImpact = false;

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

	UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;
	
public:
	ANaraProjectile();

protected:
	virtual void BeginPlay() override;

	void OnHit();

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

};
