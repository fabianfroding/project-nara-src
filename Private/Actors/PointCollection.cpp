// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Actors/PointCollection.h"

#include "Components/BillboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Libraries/NaraAbilitySystemLibrary.h"

APointCollection::APointCollection()
{
	PrimaryActorTick.bCanEverTick = false;

	auto CreatePointWithBillboard = [this](FName PointName) -> USceneComponent*
		{
			USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(PointName);
			ImmutablePts.Add(SceneComponent);

			UBillboardComponent* Billboard = CreateDefaultSubobject<UBillboardComponent>(*FString(PointName.ToString() + TEXT("_Billboard")));
			Billboard->SetupAttachment(SceneComponent);

			if (GetRootComponent())
				SceneComponent->SetupAttachment(GetRootComponent());
			else
				SetRootComponent(SceneComponent);

			return SceneComponent;
		};

	Pt_00 = CreatePointWithBillboard("Pt_00");
	Pt_01 = CreatePointWithBillboard("Pt_01");
	Pt_02 = CreatePointWithBillboard("Pt_02");
	Pt_03 = CreatePointWithBillboard("Pt_03");
	Pt_04 = CreatePointWithBillboard("Pt_04");
	Pt_05 = CreatePointWithBillboard("Pt_05");
	Pt_06 = CreatePointWithBillboard("Pt_06");
	Pt_07 = CreatePointWithBillboard("Pt_07");
	Pt_08 = CreatePointWithBillboard("Pt_08");
	Pt_09 = CreatePointWithBillboard("Pt_09");
	Pt_10 = CreatePointWithBillboard("Pt_10");
}

void APointCollection::BeginPlay()
{
	Super::BeginPlay();
}

TArray<USceneComponent*> APointCollection::GetGroundPoints(const FVector& GroundLocation, int32 NumPoints, float YawOverride)
{
	checkf(ImmutablePts.Num() >= NumPoints, TEXT("Attempted to access ImmutablePts out of bounds."));
	TArray<USceneComponent*> ArrayCopy;
	for (USceneComponent* Pt : ImmutablePts)
	{
		if (ArrayCopy.Num() >= NumPoints) return ArrayCopy;
		if (Pt != Pt_00)
		{
			FVector ToPoint = Pt->GetComponentLocation() - Pt_00->GetComponentLocation();
			ToPoint = ToPoint.RotateAngleAxis(YawOverride, FVector::UpVector);
			Pt->SetWorldLocation(Pt_00->GetComponentLocation() + ToPoint);
		}
		const FVector RaisedLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, Pt->GetComponentLocation().Z + 500.f);
		const FVector LoweredLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, Pt->GetComponentLocation().Z - 500.f);
		FHitResult HitResult;
		TArray<AActor*> IgnoreActors;
		UNaraAbilitySystemLibrary::GetAlivePlayersInRadius(this, IgnoreActors, TArray<AActor*>(), 1500.f, GetActorLocation());
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoreActors);
		GetWorld()->LineTraceSingleByProfile(HitResult, RaisedLocation, LoweredLocation, FName("BlockAll"), QueryParams);
		const FVector AdjustedLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, HitResult.ImpactPoint.Z);
		Pt->SetWorldLocation(AdjustedLocation);
		Pt->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));
		ArrayCopy.Add(Pt);
	}
	return ArrayCopy;
}
