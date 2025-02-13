// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Actors/Portal.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/NaraPlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"

bool APortal::bPortalActive = false;

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	// TODO: Create box and spline components here instead of Blueprints.
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	CachedSplineLength = GetSplineComponent()->GetSplineLength();

	UNaraCombatManager::Get()->OnEnemyDeath.AddUniqueDynamic(this, &APortal::HandleCombatEvent);
}

void APortal::StartPortal(AActor* TriggeringActor)
{
	if (bPortalActive)
		return;

	NaraPlayerCharacter = Cast<ANaraPlayerCharacter>(TriggeringActor);
	if (!NaraPlayerCharacter)
		return;

	bPortalActive = true;

	NaraPlayerCharacter->GetMesh()->SetVisibility(false);

	ActivePortalVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(PortalUpdateVFX, NaraPlayerCharacter->GetRootComponent(),
		NAME_None, FVector(), FRotator(), EAttachLocation::SnapToTarget, false);

	UGameplayStatics::SpawnSoundAtLocation(this, PortalStartSFX, NaraPlayerCharacter->GetActorLocation());
	ActiveLoopSFX = UGameplayStatics::SpawnSoundAttached(PortalLoopSFX, NaraPlayerCharacter->GetRootComponent());

	if (PortalEffectClass)
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(NaraPlayerCharacter))
			PortalEffectHandle = ASC->ApplyGameplayEffectToTarget(PortalEffectClass->GetDefaultObject<UGameplayEffect>(), ASC);
	}

	GetPortalTimeline()->PlayFromStart();
}

void APortal::PortalUpdate(float Value)
{
	if (NaraPlayerCharacter)
		NaraPlayerCharacter->SetActorLocation(GetSplineComponent()->GetLocationAtDistanceAlongSpline(Value * CachedSplineLength, ESplineCoordinateSpace::World));
}

void APortal::PortalFinish()
{
	NaraPlayerCharacter->GetCharacterMovement()->Velocity = FVector();
	NaraPlayerCharacter->GetMesh()->SetVisibility(true);

	ActivePortalVFX->DestroyComponent();

	ActiveLoopSFX->Stop();
	ActiveLoopSFX->DestroyComponent();

	UGameplayStatics::SpawnSoundAtLocation(this, PortalFinishSFX, NaraPlayerCharacter->GetActorLocation());

	if (PortalEffectHandle.IsValid())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(NaraPlayerCharacter))
			ASC->RemoveActiveGameplayEffect(PortalEffectHandle);
	}

	NaraPlayerCharacter = nullptr;
	bPortalActive = false;
}

void APortal::HandleCombatEvent(FNaraCombatEvent& CombatEvent)
{
	UNaraCombatManager::Get()->OnEnemyDeath.RemoveDynamic(this, &APortal::HandleCombatEvent);

	if (CombatEvent.CombatEventTag.MatchesTag(CombatEventActivationTag))
		CombatEventHandled(CombatEvent);
}
