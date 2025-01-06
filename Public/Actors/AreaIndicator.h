// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AreaIndicator.generated.h"

UCLASS()
class NARA_API AAreaIndicator : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDecalComponent> AreaIndicatorDecal;
	
public:	
	AAreaIndicator();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
