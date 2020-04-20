// Copyright Wesley Earl Stander 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Tank Barrel properties and mesh
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    void Elevate(float RelativeSpeed);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 20.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinimumDegrees = 0.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaximumDegrees = 40.f;
};
