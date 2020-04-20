// Copyright Wesley Earl Stander 2020

#include "UnrealEngine.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {

		MoveToActor(GetPlayerTank(), AcceptanceRadius);

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		GetControlledTank()->Fire();
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (player)
		return Cast<ATank>(player);
	else return nullptr;
}
