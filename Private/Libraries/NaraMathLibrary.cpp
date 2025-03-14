// Copyright Fabian Fröding 2024. All Right Reserved.

#include "Libraries/NaraMathLibrary.h"

FVector UNaraMathLibrary::GetPointWithPolarOffset(FVector Origin, float Distance, float Angle)
{
	const float X = Origin.X + Distance * FMath::Cos(Angle * (PI / 180));
	const float Y = Origin.Y + Distance * FMath::Sin(Angle * (PI / 180));
	return FVector(X, Y, Origin.Z);
}
