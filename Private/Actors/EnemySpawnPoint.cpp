// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Actors/EnemySpawnPoint.h"

#include "Characters/NaraEnemyCharacter.h"

void AEnemySpawnPoint::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ANaraEnemyCharacter* Enemy = GetWorld()->SpawnActorDeferred<ANaraEnemyCharacter>(EnemyClass, GetActorTransform());
	Enemy->FinishSpawning(GetActorTransform());
	Enemy->SpawnDefaultController();
}
