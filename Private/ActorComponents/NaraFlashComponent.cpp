// Copyright Fabian Fröding 2024. All Right Reserved.

#include "ActorComponents/NaraFlashComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

UNaraFlashComponent::UNaraFlashComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNaraFlashComponent::BeginPlay()
{
	Super::BeginPlay();

	if (FlashDuration <= 0.f || FlashMaterialInstance == nullptr)
		return;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner == nullptr)
		return;

	// Try get static or skeletal mesh.
	MeshComponent = Cast<UPrimitiveComponent>(ComponentOwner->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (MeshComponent == nullptr)
		MeshComponent = Cast<UPrimitiveComponent>(ComponentOwner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (MeshComponent == nullptr)
		return;

	DefaultMaterial = MeshComponent->GetMaterial(0);

	// TODO: Subscribe to on damaged event.
}

void UNaraFlashComponent::StartFlash()
{
	if (FlashDuration <= 0.f || DefaultMaterial == nullptr)
		return;

	UWorld* WorldContext = GetWorld();
	if (WorldContext == nullptr)
		return;

	MeshComponent->SetMaterial(0, FlashMaterialInstance);

	WorldContext->GetTimerManager().SetTimer(
		FlashTimerHandle, this, &UNaraFlashComponent::ResetFlash, FlashDuration, false);
}

void UNaraFlashComponent::ResetFlash()
{
	MeshComponent->SetMaterial(0, DefaultMaterial);
}

void UNaraFlashComponent::OnDamaged()
{
	StartFlash();
}
