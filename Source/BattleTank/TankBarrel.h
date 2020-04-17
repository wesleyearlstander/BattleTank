// Copyright Wesley Earl Stander 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    void Elevate(float RelativeSpeed);

private:
    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxDegreesPerSecond = 20.f;

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MinimumDegrees = 0.f;

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaximumDegrees = 40.f;
};
