// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameInstance.h"

void UNaraGameInstance::SaveEnemyStates(UWorld* World)
{
    /*for (AActor* Enemy : SublevelEnemies)
    {
        if (AEnemy* EnemyActor = Cast<AEnemy>(Enemy))
        {
            FEnemyState EnemyState;
            EnemyState.EnemyID = EnemyActor->EnemyID;
            EnemyState.Position = EnemyActor->GetActorLocation();
            EnemyState.Rotation = EnemyActor->GetActorRotation();
            EnemyState.Health = EnemyActor->CurrentHealth;
            EnemyState.bIsAlive = EnemyActor->bIsAlive;

            EnemyStates.Add(EnemyState.EnemyID, EnemyState);
        }
    }*/
}

void UNaraGameInstance::LoadEnemyStates(UWorld* World)
{
    /*for (AActor* Enemy : SublevelEnemies)
    {
        if (AEnemy* EnemyActor = Cast<AEnemy>(Enemy))
        {
            FEnemyState* SavedState = EnemyStates.Find(EnemyActor->EnemyID);
            if (SavedState)
            {
                EnemyActor->SetActorLocation(SavedState->Position);
                EnemyActor->SetActorRotation(SavedState->Rotation);
                EnemyActor->CurrentHealth = SavedState->Health;
                EnemyActor->bIsAlive = SavedState->bIsAlive;

                if (!SavedState->bIsAlive)
                {
                    EnemyActor->Destroy();
                }
            }
        }
    }*/
}
