// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameMode.h"

#include "Core/NaraCombatManager.h"

void ANaraGameMode::BeginPlay()
{
	Super::BeginPlay();

	UNaraCombatManager* CombatManager = NewObject<UNaraCombatManager>(this, UNaraCombatManager::StaticClass());
	CombatManager->Initialize();
}
