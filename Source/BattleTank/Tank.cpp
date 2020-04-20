// Copyright Wesley Earl Stander 2020

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TimerManager.h"
#include "TankMovementComponent.h"
#include "Components/InputComponent.h"
#include "UnrealEngine.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("Aiming Component")));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName(TEXT("Movement Component")));
}

void ATank::Fire()
{
	if (!TankAimingComponent->Barrel ||
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
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::SetBarrel(UTankBarrel* Barrel)
{
	TankAimingComponent->SetBarrel(Barrel);
}

void ATank::SetTurret(UTankTurret* Turret)
{
	TankAimingComponent->SetTurret(Turret);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::Reload()
{
	CanFire = true;
}
