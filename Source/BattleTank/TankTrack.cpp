// Copyright Wesley Earl Stander 2020


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	Throttle = FMath::Clamp<float>(Throttle, -1.f, 1.f);

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}