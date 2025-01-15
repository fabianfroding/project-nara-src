// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraCombatManager.h"

UNaraCombatManager* UNaraCombatManager::CombatManager;

void UNaraCombatManager::Initialize()
{
	UNaraCombatManager::CombatManager = this;
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

void UNaraCombatManager::EncounterStarted(const FGameplayTag CombatEventTag) const
{
	FNaraCombatEvent CombatEvent = { CombatEventTag };
	OnEncounterStarted.Broadcast(CombatEvent);
}
