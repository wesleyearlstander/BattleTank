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

void UTankAimingComponent::BeginPlay() 
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UTankAimingComponent::Reload, ReloadTime);
	FiringState = EFiringState::Reloading;
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
	if (FiringState != EFiringState::Reloading) {
		if (IsBarrelMoving()) {
			FiringState = EFiringState::Aiming;
		}
		else {
			FiringState = EFiringState::Locked;
		}
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint) ||
		FiringState == EFiringState::Reloading)
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
	FiringState = EFiringState::Reloading;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UTankAimingComponent::Reload, ReloadTime);
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel();
	}
}

void UTankAimingComponent::Reload()
{
	FiringState = EFiringState::Aiming;
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::MoveBarrel()
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator Delta = AimRotation - BarrelRotation;
	Barrel->Elevate(Delta.Pitch);
	if(FMath::Abs(Delta.Yaw) < 180)
		Turret->Rotate(Delta.Yaw);
	else Turret->Rotate(-Delta.Yaw);
}

