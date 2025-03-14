// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NaraMusicManager.generated.h"

UCLASS()
class NARA_API ANaraMusicManager : public AActor
{
	GENERATED_BODY()
	
public:
	ANaraMusicManager();

protected:
	virtual void BeginPlay() override;

};
