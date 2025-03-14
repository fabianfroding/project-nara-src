// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/NaraHUD.h"

#include "NaraGameHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UNaraUserWidget;

UCLASS()
class NARA_API ANaraGameHUD : public ANaraHUD
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UNaraUserWidget> OverlayWidget;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNaraUserWidget> OverlayWidgetClass;

public:

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
};
