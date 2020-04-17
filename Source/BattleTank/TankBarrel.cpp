// Copyright Wesley Earl Stander 2020


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(rawElevation, MinimumDegrees, MaximumDegrees);
	SetRelativeRotation(FRotator(Elevation, RelativeRotation.Yaw, RelativeRotation.Roll));
}