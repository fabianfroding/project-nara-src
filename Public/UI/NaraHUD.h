// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "NaraHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UNaraUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;

UCLASS()
class NARA_API ANaraHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UNaraUserWidget> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNaraUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

};
