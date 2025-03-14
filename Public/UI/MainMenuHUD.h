// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/NaraHUD.h"

#include "MainMenuHUD.generated.h"

class ULoadScreenWidget;

UCLASS()
class NARA_API AMainMenuHUD : public ANaraHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadScreenWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULoadScreenWidget> LoadScreenWidget;

protected:
	virtual void BeginPlay() override;

};
