// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameMode.h"

#include "Core/NaraSaveGame.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ANaraGameMode::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(DefaultMapName, DefaultMap);
}

AActor* ANaraGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors); // TODO: Can be registered in an array to avoid uising get all actors.
	if (!Actors.IsEmpty())
	{
		AActor* SelectedActor = Actors[0];
		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == FName("TheTag"))
				{
					SelectedActor = PlayerStart;
					break;
				}
			}
		}
		return SelectedActor;
	}
	return nullptr;
}

void ANaraGameMode::DeleteSaveSlot(const FString& SlotName, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
		UGameplayStatics::DeleteGameInSlot(SlotName, SlotIndex);
}

void ANaraGameMode::SaveSlotData(const FString SlotName, const int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
		UGameplayStatics::DeleteGameInSlot(SlotName, SlotIndex);
	
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
	
	UNaraSaveGame* NaraSaveGame = Cast<UNaraSaveGame>(SaveGameObject);
	NaraSaveGame->bSlotOccupied = true;
	//NaraSaveGame->MapName = LoadSlot->GetMapName();

	UGameplayStatics::SaveGameToSlot(NaraSaveGame, SlotName, SlotIndex);
}

UNaraSaveGame* ANaraGameMode::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
{
	USaveGame* SaveGameObject = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	else
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(SaveGameClass);

	UNaraSaveGame* NaraSaveGame = Cast<UNaraSaveGame>(SaveGameObject);
	return NaraSaveGame;
}

void ANaraGameMode::TravelToMap(const FString MapName)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Maps.FindChecked(MapName));
}
