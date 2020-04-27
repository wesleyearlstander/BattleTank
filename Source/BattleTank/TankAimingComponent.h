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
class AProjectile;

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
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UTankBarrel* Barrel = nullptr;

	UFUNCTION(BlueprintCallable)
	EFiringState GetFiringState() const;

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ReloadTime = 3.f;

	FTimerHandle ReloadTimer;
	void Reload();
	
	UTankTurret* Turret = nullptr;
	FVector AimDirection;
	bool IsBarrelMoving();

	void MoveBarrel();
};
