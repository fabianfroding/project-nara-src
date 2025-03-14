// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

#include "CombatTypes.generated.h"

USTRUCT(BlueprintType)
struct NARA_API FNaraFlash
{
	GENERATED_BODY()

private:
	FTimerHandle FlashTimerHandle;

	UPROPERTY()
	UPrimitiveComponent* MeshComponent = nullptr;

	UPROPERTY()
	UMaterialInterface* DefaultMaterial = nullptr;

public:
	UPROPERTY(EditAnywhere)
	float FlashDuration = 0.f;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* FlashMaterialInstance = nullptr;

public:
	FNaraFlash() {}

	void Initialize(ACharacter* OwningCharacter)
	{
		MeshComponent = OwningCharacter->GetMesh();

		if (MeshComponent)
			DefaultMaterial = MeshComponent->GetMaterial(0);
	}

	void StartFlash(UWorld* World)
	{
		if (!MeshComponent || !FlashMaterialInstance)
			return;

		MeshComponent->SetMaterial(0, FlashMaterialInstance);

		if (World)
			World->GetTimerManager().SetTimer(FlashTimerHandle, [this]() { EndFlash(); }, FlashDuration, false);
	}

	void EndFlash()
	{
		if (MeshComponent && DefaultMaterial)
			MeshComponent->SetMaterial(0, DefaultMaterial);
	}

	void OnDamaged(UWorld* World)
	{
		StartFlash(World);
	}
};
