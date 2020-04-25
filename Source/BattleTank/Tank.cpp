// Copyright Wesley Earl Stander 2020

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TimerManager.h"
#include "Components/InputComponent.h"
#include "UnrealEngine.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("Aiming Component")));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName(TEXT("Movement Component")));
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::Fire()
{
	if (!ensure(TankAimingComponent)) { return; }
	if (ensure(!TankAimingComponent->Barrel) ||
		!CanFire) 
	{ return; }
	
	FActorSpawnParameters p;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		TankAimingComponent->Barrel->GetSocketLocation(FName("LaunchSocket")),
		TankAimingComponent->Barrel->GetSocketRotation(FName("LaunchSocket"))
		);

	Projectile->LaunchProjectile(LaunchSpeed);
	CanFire = false;
	GetWorldTimerManager().SetTimer(ReloadTimer, this, &ATank::Reload, ReloadTime);
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::Reload()
{
	CanFire = true;
}
