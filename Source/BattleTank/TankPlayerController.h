// Copyright Wesley Earl Stander 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

//Tank player controller
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimComp);

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D& Location, FVector& Direction) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXPercentage = .5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYPercentage = .33333f;

	UPROPERTY(EditDefaultsOnly)
	float TargetRange = 100000.f;
};
