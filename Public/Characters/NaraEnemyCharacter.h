// Copyright Fabian Fr�ding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NaraCharacterBase.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/EnemyInterface.h"

#include "NaraEnemyCharacter.generated.h"

class UBehaviorTree;
class ANaraAIController;
class UNiagaraSystem;
class USoundBase;

UENUM(BlueprintType)
enum class E_NaraAIState : uint8
{
	E_Default	UMETA(DisplayName = "Default"),
	E_Idle		UMETA(DisplayName = "Idle"),
	E_Chase		UMETA(DisplayName = "Chase")
};

UCLASS()
class NARA_API ANaraEnemyCharacter : public ANaraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	// Tag broadcasted upon death.
	UPROPERTY(EditAnywhere)
	FGameplayTag EnemyDeathTag;

	UPROPERTY(BlueprintReadWrite)
	E_NaraAIState AIState = E_NaraAIState::E_Idle;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentPatrolIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsRanged = false; // If more types are needed, consider using gameplay tags or enums.

	/* OnDestroy FX */
	UPROPERTY(EditDefaultsOnly, Category = "NaraEnemyCharacter|OnDestroyFX")
	TObjectPtr<UNiagaraSystem> OnDestroyVFX;

	UPROPERTY(EditDefaultsOnly, Category = "NaraEnemyCharacter|OnDestroyFX")
	TObjectPtr<USoundBase> OnDestroySFX;
	/* End OnDestroy FX */

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ANaraAIController> NaraAIController;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> PatrolLocations;

	UPROPERTY(BlueprintReadOnly)
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeathLifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> CombatTarget;

public:
	ANaraEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	/* Combat Interface */
	virtual void Die() override;

	/* Enemy Interface */
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnLoot();

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	virtual void Destroyed() override;

private:
	void GiveStartupAbilities();
	
};
