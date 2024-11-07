// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/NaraGameMode.h"

#include "Pawns/NaraCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANaraGameMode::ANaraGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
