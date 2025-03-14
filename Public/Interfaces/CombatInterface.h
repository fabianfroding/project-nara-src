// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"

#include "CombatInterface.generated.h"

class UAbilitySystemComponent;
class UAnimMontage;
class UNiagaraSystem;
class USoundBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, DeadActor);

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketTag;
};

UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class NARA_API ICombatInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& SocketTag);

	virtual void Die() = 0;

	virtual FOnDeathSignature& GetOnDeathDelegate() = 0;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTaggedMontage> GetAttackMontages();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetHurtVFX();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetMinionCount();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IncrementMinionCount(int32 Amount);

	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() = 0;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInShockLoop(bool bInLoop);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USkeletalMeshComponent* GetWeapon();

	virtual void StartFlash() = 0;

};
