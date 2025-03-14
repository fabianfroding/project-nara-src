// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Core/NaraCheckpoint.h"

#include "Characters/NaraPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Core/NaraGameMode.h"
#include "Kismet/GameplayStatics.h"

ANaraCheckpoint::ANaraCheckpoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = false;

    CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>("CheckpointMesh");
    CheckpointMesh->SetupAttachment(GetRootComponent());
    CheckpointMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CheckpointMesh->SetCollisionResponseToAllChannels(ECR_Block);

    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
    Sphere->SetupAttachment(CheckpointMesh);
    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ANaraCheckpoint::LoadActor_Implementation()
{
    if (bReached)
    {
        HandleGlowEffects();
    }
}

void ANaraCheckpoint::BeginPlay()
{
    Super::BeginPlay();
    Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANaraCheckpoint::OnSphereOverlap);
}

void ANaraCheckpoint::HandleGlowEffects()
{
    Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    UMaterialInstanceDynamic* DynamicMaterialInstace = UMaterialInstanceDynamic::Create(CheckpointMesh->GetMaterial(0), this);
    CheckpointMesh->SetMaterial(0, DynamicMaterialInstace);
    CheckpointReached(DynamicMaterialInstace);
}

void ANaraCheckpoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ANaraPlayerCharacter* NaraPlayerCharacter = Cast<ANaraPlayerCharacter>(OtherActor))
    {
        bReached = true;

        if (ANaraGameMode* NaraGM = Cast<ANaraGameMode>(UGameplayStatics::GetGameMode(this)))
        {
            const UWorld* World = GetWorld();
            FString MapName = World->GetMapName();
            MapName.RemoveFromStart(World->StreamingLevelsPrefix);

            NaraGM->SaveWorldState(GetWorld());
        }

        NaraPlayerCharacter->SaveProgress(PlayerStartTag);
        HandleGlowEffects();
    }
}
