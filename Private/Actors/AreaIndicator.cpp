// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Actors/AreaIndicator.h"

#include "Components/DecalComponent.h"

AAreaIndicator::AAreaIndicator()
{
	PrimaryActorTick.bCanEverTick = true;

	AreaIndicatorDecal = CreateDefaultSubobject<UDecalComponent>("AreaIndicatorDecal");
	AreaIndicatorDecal->SetupAttachment(GetRootComponent());
}

void AAreaIndicator::BeginPlay()
{
	Super::BeginPlay();
}

void AAreaIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
