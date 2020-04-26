// Copyright Wesley Earl Stander 2020

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("Aiming Component")));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName(TEXT("Movement Component")));
	PrimaryActorTick.bCanEverTick = false;
}