// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameMode.h"

#include "Core/NaraGameInstance.h"
#include "Core/NaraSaveGame.h"
#include "EngineUtils.h"
#include "Interfaces/SaveInterface.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

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

void ANaraGameMode::SaveWorldState(UWorld* World)
{
	FString WorldName = World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	UNaraGameInstance* AuraGI = Cast<UNaraGameInstance>(GetGameInstance());
	check(AuraGI);

	if (UNaraSaveGame* SaveGame = GetSaveSlotData(AuraGI->LoadSlotName, AuraGI->LoadSlotIndex))
	{
		if (!SaveGame->HasMap(WorldName))
		{
			FSavedMap NewSavedMap;
			NewSavedMap.MapAssetName = WorldName;
			SaveGame->SavedMaps.Add(NewSavedMap);
		}

		FSavedMap SavedMap = SaveGame->GetSavedMapWithMapName(WorldName);
		SavedMap.SavedActors.Empty();

		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;

			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>())
				continue;

			FSavedActor SavedActor;
			SavedActor.ActorName = Actor->GetFName();
			SavedActor.Transform = Actor->GetTransform();

			FMemoryWriter MemoryWriter(SavedActor.Bytes);

			FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
			Archive.ArIsSaveGame = true;

			Actor->Serialize(Archive);

			SavedMap.SavedActors.AddUnique(SavedActor);
		}

		for (FSavedMap& MapToReplace : SaveGame->SavedMaps)
		{
			if (MapToReplace.MapAssetName == WorldName)
			{
				MapToReplace = SavedMap;
			}
		}
		UGameplayStatics::SaveGameToSlot(SaveGame, AuraGI->LoadSlotName, AuraGI->LoadSlotIndex);
	}
}

void ANaraGameMode::TravelToMap(const FString MapName)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Maps.FindChecked(MapName));
}
