// Copyright Fabian Fröding 2025. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/SaveInterface.h"
#include "GameFramework/PlayerStart.h"

#include "NaraCheckpoint.generated.h"

class USphereComponent;

UCLASS()
class NARA_API ANaraCheckpoint : public APlayerStart, public ISaveInterface
{
	GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> CheckpointMesh;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USphereComponent> Sphere;

public:
    UPROPERTY(BlueprintReadOnly, SaveGame)
    bool bReached = false;

public:
    ANaraCheckpoint(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION()
    virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent)
    void CheckpointReached(UMaterialInstanceDynamic* DynamicMaterialInstance); \

    void HandleGlowEffects();

};
