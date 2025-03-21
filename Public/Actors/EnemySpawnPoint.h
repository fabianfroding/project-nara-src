// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"

#include "EnemySpawnPoint.generated.h"

class ANaraEnemyCharacter;

UCLASS()
class NARA_API AEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class")
	TSubclassOf<ANaraEnemyCharacter> EnemyClass;

};
