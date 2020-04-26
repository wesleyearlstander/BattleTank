// Copyright Wesley Earl Stander 2020

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "UnrealEngine.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint) ||
		!CanFire)
	{
		return;
	}

	FActorSpawnParameters p;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("LaunchSocket")),
		Barrel->GetSocketRotation(FName("LaunchSocket"))
		);

	Projectile->LaunchProjectile(LaunchSpeed);
	CanFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UTankAimingComponent::Reload, ReloadTime);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }
	
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName(TEXT("LaunchSocket")));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::Reload()
{
	CanFire = true;
}


void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator Delta = AimRotation - BarrelRotation;
	Barrel->Elevate(Delta.Pitch);
	Turret->Rotate(Delta.Yaw);
}

