// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"

#include "NaraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

UCLASS(Abstract)
class NARA_API ANaraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere)
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere)
	FName UnarmedLeftSocketName;

	UPROPERTY(EditAnywhere)
	FName UnarmedRightSocketName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitReactMontage;

	bool bDead = false;

public:
	UPROPERTY(EditAnywhere)
	TArray<FTaggedMontage> AttackMontages;

public:
	ANaraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void AddCharacterAbilities();

	/* Combat Interface Functions */
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	/* End Combat Interface Functions */

	virtual void HandleDeath();

protected:
	virtual void InitAbilityActorInfo();

	void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

};
