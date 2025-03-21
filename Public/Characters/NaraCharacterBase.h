// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "Types/CombatTypes.h"

#include "NaraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UAttributeSet;
class UDebuffNiagaraComponent;
class UGameplayAbility;
class UGameplayEffect;
class UNiagaraSystem;
class UPassiveNiagaraComponent;
class USoundBase;

UCLASS(Abstract)
class NARA_API ANaraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere)
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere)
	FName UnarmedLeftSocketName;

	UPROPERTY(EditAnywhere)
	FName UnarmedRightSocketName;

	UPROPERTY(EditAnywhere)
	FName TailSocketName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(BlueprintReadOnly)
	bool bDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* HurtVFX;

	// TODO: Remove this and replace with sound notify when assets with death animations are imported.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* DeathSFX;

	int32 MinionCount = 0;

	UPROPERTY(EditDefaultsOnly)
	FNaraFlash FlashHandler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDebuffNiagaraComponent> StunDebuffComponent;

public:
	UPROPERTY(EditAnywhere)
	TArray<FTaggedMontage> AttackMontages;

	UPROPERTY(BlueprintReadOnly)
	bool bIsStunned = false;

	FOnASCRegistered OnAscRegistered;
	FOnDeathSignature OnDeathDelegate;

public:
	ANaraCharacterBase();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void AddCharacterAbilities();

	/* Combat Interface Functions */
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& SocketTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;
	virtual FOnDeathSignature& GetOnDeathDelegate() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetHurtVFX_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;
	virtual USkeletalMeshComponent* GetWeapon_Implementation() override;
	virtual void StartFlash();
	/* End Combat Interface Functions */

	virtual void HandleDeath();

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

};
