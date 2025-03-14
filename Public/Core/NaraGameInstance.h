// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "NaraGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FEnemyState
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString EnemyID;

    UPROPERTY(BlueprintReadWrite)
    FVector Position;

    UPROPERTY(BlueprintReadWrite)
    FRotator Rotation;

    UPROPERTY(BlueprintReadWrite)
    float Health;

    UPROPERTY(BlueprintReadWrite)
    bool bIsAlive;
};

UCLASS()
class NARA_API UNaraGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadWrite)
    TMap<FString, FEnemyState> EnemyStates;

    UPROPERTY()
    FName PlayerStartTag = FName();

    UPROPERTY()
    FString LoadSlotName = FString();

    UPROPERTY()
    int32 LoadSlotIndex = 0;

public:
    void SaveEnemyStates(UWorld* World);
    void LoadEnemyStates(UWorld* World);

};
