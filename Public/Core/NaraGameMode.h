// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "NaraGameMode.generated.h"

class UNaraSaveGame;
class ULootTiers;
class USaveGame;

UCLASS(minimalapi)
class ANaraGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> SaveGameClass;

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;

	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Loot Tiers")
	TObjectPtr<ULootTiers> LootTiers;

protected:
	virtual void BeginPlay() override;

public:
	FString GetMapNameFromMapAssetName(const FString& MapAssetName) const;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	void PlayerDied(ACharacter* DeadCharacter);

	static void DeleteSaveSlot(const FString& SlotName, int32 SlotIndex);

	// Call this from the main menu when a new game is created.
	void SaveSlotData(const FString SlotName, const int32 SlotIndex);

	UNaraSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;

	UNaraSaveGame* RetrieveInGameSaveData();
	void SaveInGameProgressData(UNaraSaveGame* SaveObject);

	void SaveWorldState(UWorld* World, const FString& DestinationMapAssetName = FString("")) const;
	void LoadWorldState(UWorld* World) const;

	void TravelToMap(const FString MapName);

};
