// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Types/NaraAbilityTypes.h"

#include "NaraProjectile.generated.h"

class UGameplayEffect;
class UNiagaraSystem;
class UProjectileMovementComponent;
class USoundBase;
class USphereComponent;

UCLASS()
class NARA_API ANaraProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> HitActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	// Effects applied to the owner on hits.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> OnHitGrantedGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag InstantGameplayEffectMagnitudeTag;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactVFX;

	/* Sounds */
	UPROPERTY(EditAnywhere, Category = "NaraProjectile|Sounds")
	TObjectPtr<USoundBase> LaunchSFX;

	UPROPERTY(EditAnywhere, Category = "NaraProjectile|Sounds")
	TObjectPtr<USoundBase> ImpactSFX;

	UPROPERTY(EditAnywhere, Category = "NaraProjectile|Sounds")
	TObjectPtr<USoundBase> LoopingSFX;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSFXComponent;
	/* End Sounds*/

	UPROPERTY(EditDefaultsOnly)
	bool bIgnoreInstigator = true;

	UPROPERTY(EditDefaultsOnly)
	bool bPiercing = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

	UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;
	
public:
	ANaraProjectile();

	bool HasHit() { return !HitActors.IsEmpty(); }

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	bool IsValidOverlap(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	virtual void OnHit();

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void ResetHitActors() { HitActors.Empty(); }

};
