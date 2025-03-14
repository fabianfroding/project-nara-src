// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AreaIndicator.generated.h"

UCLASS()
class NARA_API AAreaIndicator : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDecalComponent> AreaIndicatorDecal;
	
public:	
	AAreaIndicator();

	void SetDecalMaterial(UMaterialInterface* DecalMaterial) const;

};
