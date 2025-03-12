// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameMode.h"

#include "Core/NaraGameInstance.h"
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
	UNaraGameInstance* NaraGameInstance = Cast<UNaraGameInstance>(GetGameInstance());

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors); // TODO: Can be registered in an array to avoid using get all actors.
	if (!Actors.IsEmpty())
	{
		AActor* SelectedActor = Actors[0];
		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == FName(NaraGameInstance->PlayerStartTag))
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
	//NaraSaveGame->PlayerStartTag = LoadSlot->PlayerStartTag;

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

UNaraSaveGame* ANaraGameMode::RetrieveInGameSaveData()
{
	UNaraGameInstance* NaraGameInstance = Cast<UNaraGameInstance>(GetGameInstance());
	const FString InGameLoadSlotName = NaraGameInstance->LoadSlotName;
	const int32 InGameLoadSlotIndex = NaraGameInstance->LoadSlotIndex;
	return GetSaveSlotData(InGameLoadSlotName, InGameLoadSlotIndex);
}

void ANaraGameMode::SaveInGameProgressData(UNaraSaveGame* SaveObject)
{
	UNaraGameInstance* NaraGameInstance = Cast<UNaraGameInstance>(GetGameInstance());

	const FString InGameLoadSlotName = NaraGameInstance->LoadSlotName;
	const int32 InGameLoadSlotIndex = NaraGameInstance->LoadSlotIndex;
	NaraGameInstance->PlayerStartTag = SaveObject->PlayerStartTag;

	UGameplayStatics::SaveGameToSlot(SaveObject, InGameLoadSlotName, InGameLoadSlotIndex);
}

void ANaraGameMode::TravelToMap(const FString MapName)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Maps.FindChecked(MapName));
}
