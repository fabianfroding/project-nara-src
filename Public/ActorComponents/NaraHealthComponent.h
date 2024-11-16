// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NaraHealthComponent.generated.h"

class UNaraHealthSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamaged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NARA_API UNaraHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	float InvincibilityFramesTime;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	const UNaraHealthSet* HealthAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	float InvincibilityFramesDuration = 0.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDie OnDie;

	UPROPERTY(BlueprintAssignable)
	FOnDamaged OnDamaged;

public:
	UNaraHealthComponent();

	UFUNCTION(BlueprintPure)
	static UNaraHealthComponent* FindHealthComponent(const AActor* Actor) 
	{
		return (Actor ? Actor->FindComponentByClass<UNaraHealthComponent>() : nullptr);
	}

	UFUNCTION(BlueprintCallable)
	void TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource);
	const UNaraHealthSet* GetHealthSet() { return HealthAttributeSet; }

	bool IsAlive() const;
	bool IsInvulnerable();

private:
	void HandleDeath();
		
};
