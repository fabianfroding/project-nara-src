// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NaraHealthComponent.generated.h"

class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NARA_API UNaraHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	/* GAS Variables */
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	const class UNaraHealthSet* HealthAttributeSet;
	/* End GAS Variables */

	UPROPERTY(EditDefaultsOnly)
	float InvincibilityFramesDuration = 0.f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDie OnDie;

public:
	UNaraHealthComponent();

	UFUNCTION(BlueprintPure)
	static UNaraHealthComponent* FindHealthComponent(const AActor* Actor) 
	{
		return (Actor ? Actor->FindComponentByClass<UNaraHealthComponent>() : nullptr);
	}

	UFUNCTION(BlueprintCallable)
	void TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource);

	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

	void InitializeWithAbilitySystem(UAbilitySystemComponent* InASC);

	bool IsAlive() const;

protected:
	virtual void BeginPlay() override;

private:
	void HandleDeath();
		
};
