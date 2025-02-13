// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"

#include "NaraCombatManager.generated.h"

/** NaraCombatManager
 * Singleton to keep track of active combat-participating actors (to avoid having to rely of expensive GetAllActors<> functions).
 */

USTRUCT(BlueprintType)
struct FNaraCombatEvent
{
	GENERATED_BODY()

public:
	FNaraCombatEvent() {}
	FNaraCombatEvent(FGameplayTag InCombatEventTag) : CombatEventTag(InCombatEventTag) {}

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag CombatEventTag;

	UPROPERTY(BlueprintReadOnly)
	AActor* CombatActor;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatEventSignature, FNaraCombatEvent&, CombatEvent);

UCLASS()
class NARA_API UNaraCombatManager : public UObject
{
	GENERATED_BODY()
	
private:
	static UNaraCombatManager* CombatManager;

	UPROPERTY()
	TArray<AActor*> RegisteredEnemies;

public:
	UPROPERTY(BlueprintAssignable)
	FOnCombatEventSignature OnEnemyDeath;

	UPROPERTY(BlueprintAssignable)
	FOnCombatEventSignature OnEncounterStarted;

public:
	UFUNCTION(BlueprintPure)
	static UNaraCombatManager* Get();

	void RegisterEnemy(AActor* Enemy);
	void EnemyDied(AActor* Enemy, const FGameplayTag CombatEventTag);

	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetEnemies() { return RegisteredEnemies; }

private:
	void UnregisterEnemy(AActor* Enemy);

};
