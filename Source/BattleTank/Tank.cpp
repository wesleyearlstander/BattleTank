// Copyright Wesley Earl Stander 2020

#include "TankAimingComponent.h"
#include "Components/InputComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("Aiming Component")));
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
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

