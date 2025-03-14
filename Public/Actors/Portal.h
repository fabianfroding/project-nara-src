// Copyright Fabian Fröding 2024. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/NaraCombatManager.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"

#include "Portal.generated.h"

class ANaraPlayerCharacter;
class UAudioComponent;
class UBoxComponent;
class UGameplayEffect;
class UNiagaraComponent;
class UNiagaraSystem;
class USoundBase;
class USplineComponent;
class UTimelineComponent;

UCLASS()
class NARA_API APortal : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FActiveGameplayEffectHandle PortalEffectHandle;

	UAudioComponent* ActiveLoopSFX;
	UNiagaraComponent* ActivePortalVFX;
	float CachedSplineLength = 0.f;

protected:
	// Effect applied to the player while using portal, mainly to block input etc.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> PortalEffectClass;

	// Tag from combat events required for the portal to be activated/used.
	UPROPERTY(EditAnywhere)
	FGameplayTag CombatEventActivationTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* PortalUpdateVFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* PortalStartSFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* PortalLoopSFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* PortalFinishSFX;

	UPROPERTY(BlueprintReadWrite)
	ANaraPlayerCharacter* NaraPlayerCharacter;

	static bool bPortalActive;
	
public:	
	APortal();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UTimelineComponent* GetPortalTimeline() const;
	virtual UTimelineComponent* GetPortalTimeline_Implementation() const { return nullptr; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UBoxComponent* GetTriggerBoxComponent() const;
	virtual UBoxComponent* GetTriggerBoxComponent_Implementation() const { return nullptr; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USplineComponent* GetSplineComponent() const;
	virtual USplineComponent* GetSplineComponent_Implementation() const { return nullptr; }

	// Only executed if the event has tag matching required event tag.
	UFUNCTION(BlueprintImplementableEvent)
	void CombatEventHandled(FNaraCombatEvent CombatEvent);

	UFUNCTION(BlueprintCallable)
	void StartPortal(AActor* TriggeringActor);

	UFUNCTION(BlueprintCallable)
	void PortalUpdate(float Value);

	UFUNCTION(BlueprintCallable)
	void PortalFinish();

	UFUNCTION()
	void HandleCombatEvent(FNaraCombatEvent& CombatEvent);

};
