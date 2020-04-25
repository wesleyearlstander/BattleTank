// Copyright Wesley Earl Stander 2020

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector Direction = MoveVelocity.GetSafeNormal();
	FVector Forward = GetOwner()->GetActorForwardVector();

	float ForwardThrow = FVector::DotProduct(Forward, Direction);
	IntendMoveForward(ForwardThrow);

	FVector RightThrow = FVector::CrossProduct(Forward, Direction);
	IntendMoveRight(RightThrow.Z);
}
