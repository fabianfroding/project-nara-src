// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NaraCharacterBase.h"
#include "Interfaces/CombatInterface.h"
#include "Interfaces/EnemyInterface.h"
#include "UIControllers/OverlayWidgetController.h"

#include "NaraEnemyCharacter.generated.h"

class UBehaviorTree;
class ANaraAIController;

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

	UPROPERTY(BlueprintReadWrite)
	E_NaraAIState AIState = E_NaraAIState::E_Idle;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentPatrolIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsRanged = false; // If more types are needed, consider using gameplay tags or enums.

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ANaraAIController> NaraAIController;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> PatrolLocations;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintReadOnly)
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseWalkSpeed = 125.f;

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

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

private:
	void GiveStartupAbilities();
	
};
