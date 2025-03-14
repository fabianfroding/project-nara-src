// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/NaraCheckpoint.h"

#include "MapEntrance.generated.h"

UCLASS()
class NARA_API AMapEntrance : public ANaraCheckpoint
{
	GENERATED_BODY()

public:
	AMapEntrance(const FObjectInitializer& ObjectInitializer);

	/* Save Interface */
	virtual void LoadActor_Implementation() override;
	/* end Save Interface */

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> DestinationMap;

	UPROPERTY(EditAnywhere)
	FName DestinationPlayerStartTag;

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;

};
