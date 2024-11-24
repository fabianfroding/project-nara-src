// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NaraHealthComponent.generated.h"

class UAbilitySystemComponent;
class UNaraHealthSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamaged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthAttributeChanged, UNaraHealthComponent*, HealthComponent, float, OldValue, float, NewValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NARA_API UNaraHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	float InvincibilityFramesTime = 0.f;

protected:
	UPROPERTY()
	TObjectPtr<const UNaraHealthSet> HealthSet; // Reference to the health set of component owner's ASC.

	UPROPERTY(EditDefaultsOnly)
	float InvincibilityFramesDuration = 0.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDie OnDie;

	UPROPERTY(BlueprintAssignable)
	FOnDamaged OnDamaged;

	UPROPERTY(BlueprintAssignable)
	FOnHealthAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnHealthAttributeChanged OnMaxHealthChanged;

public:
	UNaraHealthComponent();

	UFUNCTION(BlueprintPure)
	static UNaraHealthComponent* FindHealthComponent(const AActor* Actor) 
	{
		return (Actor ? Actor->FindComponentByClass<UNaraHealthComponent>() : nullptr);
	}

	UFUNCTION(BlueprintCallable)
	void TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource);
	
	UFUNCTION(BlueprintPure)
	const UNaraHealthSet* GetHealthSet() { return HealthSet; }

	void InitializeWithAbilitySystem(UAbilitySystemComponent* InASC);

	bool IsAlive() const;
	bool IsInvulnerable();

protected:
	virtual void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, float OldValue, float NewValue);
	virtual void HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, float OldValue, float NewValue);

private:
	void HandleDeath();
		
};
