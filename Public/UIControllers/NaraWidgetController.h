// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "NaraWidgetController.generated.h"

class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
public:
	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC) 
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
};

UCLASS(Blueprintable)
class NARA_API UNaraWidgetController : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> ASC;

public:
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
};
