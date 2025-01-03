// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NaraFlashComponent.generated.h"

// TODO: Move this to a character class instead. It's too unnecessary performance-wise to have it as its own component.

UCLASS(meta = (BlueprintSpawnableComponent))
class NARA_API UNaraFlashComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FTimerHandle FlashTimerHandle;

	UPrimitiveComponent* MeshComponent;
	UMaterialInterface* DefaultMaterial;

protected:
	UPROPERTY(EditDefaultsOnly)
	float FlashDuration = 0.f;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* FlashMaterialInstance;

public:
	UNaraFlashComponent();

protected:
	virtual void BeginPlay() override;

private:
	void StartFlash();

	void ResetFlash();

	UFUNCTION()
	void OnDamaged();

};
