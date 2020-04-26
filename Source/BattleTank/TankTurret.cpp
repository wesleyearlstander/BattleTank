// Copyright Wesley Earl Stander 2020


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(RelativeRotation.Pitch, rawRotation, RelativeRotation.Roll));
}