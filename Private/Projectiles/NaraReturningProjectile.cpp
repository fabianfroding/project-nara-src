// Copyright Fabian Fröding 2025. All Right Reserved.

#include "Projectiles/NaraReturningProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ANaraReturningProjectile::ANaraReturningProjectile()
{
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = 0.f;
		ProjectileMovement->MaxSpeed = 0.f;
		//ProjectileMovement->bStartWithTickEnabled = false; // TODO: Find out how to turn off Start with Tick Enabled by default.
		ProjectileMovement->bAutoActivate = false;
	}
}

void ANaraReturningProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovement->SetComponentTickEnabled(false);

	InitialLocation = GetActorLocation();
	TargetLocation = InitialLocation + (GetActorForwardVector() * TravelDistance);

	if (UTimelineComponent* OutgoingTimeline = GetOutgoingTimeline())
		OutgoingTimeline->Play();
}

void ANaraReturningProjectile::Destroyed()
{
	if (ReturnedCueTag.IsValid())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetInstigator()))
		{
			FGameplayEventData EventData;
			EventData.Instigator = GetInstigator();
			EventData.Target = GetInstigator();
			EventData.EventTag = ReturnedCueTag;
			ASC->HandleGameplayEvent(ReturnedCueTag, &EventData);
		}
	}

	Super::Destroyed();
}

void ANaraReturningProjectile::OutgoingUpdate(const float Delta)
{
	SetActorLocation(UKismetMathLibrary::VLerp(InitialLocation, TargetLocation, Delta));
}

void ANaraReturningProjectile::OutgoingFinish()
{
	UGameplayStatics::PlaySoundAtLocation(this, ReturnSFX, GetActorLocation());

	if (bResetTargetsOnReturn)
		ResetHitActors();

	if (UTimelineComponent* ReturningTimeline = GetReturningTimeline())
		ReturningTimeline->Play();
}

void ANaraReturningProjectile::ReturningUpdate(const float Delta)
{
	FVector ReturnLocation = InitialLocation;
	if (ReturnToInstigator && ReturnToActor)
		ReturnLocation = ReturnToActor->GetActorLocation();

	SetActorLocation(UKismetMathLibrary::VLerp(TargetLocation, ReturnLocation, Delta));

	if (UKismetMathLibrary::VSize(GetActorLocation() - ReturnLocation) <= ReturnImpactDistance)
	{
		// Set knockback here if desired (using UNaraAbilitySystemLibrary::SetKnockbackDirection()).
		Destroy();
	}
}
