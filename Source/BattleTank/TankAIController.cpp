// Copyright Wesley Earl Stander 2020

#include "UnrealEngine.h"
#include "TankAimingComponent.h"
#include "UnrealEngine.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	AimingComponent->Fire();
}