// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "NaraGameMode.generated.h"

class USaveGame;

UCLASS(minimalapi)
class ANaraGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> SaveGameClass;

public:
	// Call this from the main menu when a new game is created.
	void SaveSlotData(const FString SlotName, const int32 SlotIndex);

};
