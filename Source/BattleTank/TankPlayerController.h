// Copyright Wesley Earl Stander 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D& Location, FVector& Direction) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXPercentage = .5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYPercentage = .33333f;

	UPROPERTY(EditAnywhere)
	float TargetRange = 100000.f;
};
