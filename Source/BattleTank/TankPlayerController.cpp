// Copyright Wesley Earl Stander 2020

#include "BattleTank.h"
#include "UnrealEngine.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UTankAimingComponent* aiming = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (aiming) {
		FoundAimingComponent(aiming);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Aiming Component not found"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	UTankAimingComponent* aiming = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aiming)) { return; }
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		aiming->AimAt(HitLocation);
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