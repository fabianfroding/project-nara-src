// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/NaraCharacter.h"

#include "NaraEnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class E_NaraAIState : uint8
{
	E_Default	UMETA(DisplayName = "Default"),
	E_Idle		UMETA(DisplayName = "Idle"),
	E_Chase		UMETA(DisplayName = "Chase")
};

UCLASS()
class NARA_API ANaraEnemyCharacter : public ANaraCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	E_NaraAIState AIState = E_NaraAIState::E_Idle;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentPatrolIndex = 0;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> PatrolLocations;

protected:
	virtual void BeginPlay() override;
	
};
