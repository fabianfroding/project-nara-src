// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraCombatManager.h"

UNaraCombatManager* UNaraCombatManager::CombatManager = nullptr;

UNaraCombatManager* UNaraCombatManager::Get()
{
	if (!CombatManager)
	{
		CombatManager = NewObject<UNaraCombatManager>();
		CombatManager->AddToRoot(); // Prevents garbage collection.
	}
	return CombatManager;
}

void UNaraCombatManager::RegisterEnemy(AActor* Enemy)
{
	RegisteredEnemies.AddUnique(Enemy);
}

void UNaraCombatManager::UnregisterEnemy(AActor* Enemy)
{
	if (!IsValid(Enemy))
		return;

	RegisteredEnemies.Remove(Enemy);
}

void UNaraCombatManager::EnemyDied(AActor* Enemy, const FGameplayTag CombatEventTag)
{
	FNaraCombatEvent CombatEvent = { CombatEventTag };
	CombatEvent.CombatActor;
	OnEnemyDeath.Broadcast(CombatEvent);
	UnregisterEnemy(Enemy);
}
