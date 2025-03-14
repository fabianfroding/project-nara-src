// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "NaraHUD.generated.h"

class UCommonActivatableWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWidgetStackEventSignature, UCommonActivatableWidget*, Widget);

UCLASS()
class NARA_API ANaraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWidgetStackEventSignature OnWidgetPushed;

	UPROPERTY(BlueprintAssignable)
	FWidgetStackEventSignature OnWidgetPopped;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ANaraHUD* GetNaraHUD(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ActivatableWidgetClass", DynamicOutputParam = "OutWidget"))
	static void PushWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, UCommonActivatableWidget*& OutWidget,
		APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	static void PopWidget(UCommonActivatableWidget* ActivatableWidget);

};
