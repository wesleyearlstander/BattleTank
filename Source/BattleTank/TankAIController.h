// Copyright Wesley Earl Stander 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

//Tank AI Controller
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Radius around player that tank will accept final movement
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000.f;

	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;
};
