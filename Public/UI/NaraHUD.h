// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "NaraHUD.generated.h"

class UNaraUserWidget;

UCLASS()
class NARA_API ANaraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UNaraUserWidget> OverlayWidget;
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNaraUserWidget> OverlayWidgetClass;

protected:
	virtual void BeginPlay() override;
};
