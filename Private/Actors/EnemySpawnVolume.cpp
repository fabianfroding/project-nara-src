// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Actors/EnemySpawnVolume.h"

#include "Actors/EnemySpawnPoint.h"
#include "Characters/NaraPlayerCharacter.h"
#include "Components/BoxComponent.h"

AEnemySpawnVolume::AEnemySpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemySpawnVolume::OnBoxOverlap);
}

void AEnemySpawnVolume::LoadActor_Implementation()
{
	if (bReached)
	{
		Destroy();
	}
}

void AEnemySpawnVolume::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANaraPlayerCharacter* NaraPlayerChar = Cast<ANaraPlayerCharacter>(OtherActor);
	if (NaraPlayerChar) return;

	bReached = true;
	for (AEnemySpawnPoint* Point : SpawnPoints)
	{
		if (IsValid(Point))
		{
			Point->SpawnEnemy();
		}
	}
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
