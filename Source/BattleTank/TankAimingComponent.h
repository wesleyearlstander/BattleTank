// Copyright Wesley Earl Stander 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UStaticMeshComponent;
class UTankBarrel;
class UTankTurret;

//Hold's barrel properties and elevate method, and aims barrel and turret
UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = state)
	EFiringState FiringState = EFiringState::Locked;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

	UTankBarrel* Barrel = nullptr;

private:
	
	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);
};
