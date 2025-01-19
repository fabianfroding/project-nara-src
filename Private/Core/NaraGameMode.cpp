// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Core/NaraGameMode.h"

#include "Core/NaraSaveGame.h"
#include "Kismet/GameplayStatics.h"

void ANaraGameMode::SaveSlotData(const FString SlotName, const int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
		UGameplayStatics::DeleteGameInSlot(SlotName, SlotIndex);
	
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
	UNaraSaveGame* NaraSaveGame = Cast<UNaraSaveGame>(SaveGameObject);
	UGameplayStatics::SaveGameToSlot(NaraSaveGame, SlotName, SlotIndex);
}
