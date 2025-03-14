// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Actors/MapEntrance.h"

#include "Characters/NaraPlayerCharacter.h"
#include "Core/NaraGameMode.h"
#include "Kismet/GameplayStatics.h"

AMapEntrance::AMapEntrance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AMapEntrance::LoadActor_Implementation()
{
	// Do nothing when loading a Map Entrance
}

void AMapEntrance::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ANaraPlayerCharacter* NaraPlayerChar = Cast<ANaraPlayerCharacter>(OtherActor))
	{
		bReached = true;

		if (ANaraGameMode* NaraGM = Cast<ANaraGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			NaraGM->SaveWorldState(GetWorld(), DestinationMap.ToSoftObjectPath().GetAssetName());
		}

		NaraPlayerChar->SaveProgress(DestinationPlayerStartTag);

		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DestinationMap);
	}
}
