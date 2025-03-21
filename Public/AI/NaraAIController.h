// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "NaraAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class NARA_API ANaraAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ANaraAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

};
