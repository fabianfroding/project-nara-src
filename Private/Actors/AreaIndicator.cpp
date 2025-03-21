// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Actors/AreaIndicator.h"

#include "Components/DecalComponent.h"

AAreaIndicator::AAreaIndicator()
{
	PrimaryActorTick.bCanEverTick = false;

	AreaIndicatorDecal = CreateDefaultSubobject<UDecalComponent>("AreaIndicatorDecal");
	AreaIndicatorDecal->SetupAttachment(GetRootComponent());
}

void AAreaIndicator::SetDecalMaterial(UMaterialInterface* DecalMaterial) const
{
	AreaIndicatorDecal->SetMaterial(0, DecalMaterial);
}
