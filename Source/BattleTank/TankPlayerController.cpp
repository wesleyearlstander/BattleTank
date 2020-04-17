// Copyright Wesley Earl Stander 2020

#include "BattleTank.h"
#include "UnrealEngine.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float CrosshairXLocation = CrossHairXPercentage * ViewportSizeX;
	float CrosshairYLocation = CrossHairYPercentage * ViewportSizeY;
	FVector2D ScreenLocation = FVector2D(CrosshairXLocation, CrosshairYLocation);
	FVector Direction;
	if (GetLookDirection(ScreenLocation, Direction)) {
		FHitResult HitResult;
		FVector Location = PlayerCameraManager->GetCameraLocation();
		FVector End = Location + (Direction * TargetRange);
		if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Location,
			End,
			ECollisionChannel::ECC_Visibility)) {
			HitLocation = HitResult.Location;
			return true;
		}
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& Direction) const
{
	FVector Location;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, Location, Direction);
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}