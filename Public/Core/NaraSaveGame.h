// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "NaraSaveGame.generated.h"

UCLASS()
class NARA_API UNaraSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex = 0;

	UPROPERTY()
	bool bSlotOccupied = false;

	UPROPERTY()
	FString MapName = FString("Default Map Name");

};
