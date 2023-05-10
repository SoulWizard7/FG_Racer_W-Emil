#pragma once

#include "GameFramework/Pawn.h"
#include "RaceCar.generated.h"

class UBoxComponent;
class URaceCarMovementComponent;
class URacePowerup;

UCLASS()
class ARaceCar : public APawn
{
	GENERATED_BODY()

public:
	ARaceCar();

	void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void SetupPlayerInputComponent(UInputComponent* InputComp) override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;
	void HandlePowerup();
	void HandleAccelerateInput(float value);
	void HandleTurnRightInput(float value);

	void EquipPowerup(URacePowerup* NewPowerup);
	bool HasEquippedPowerup() {return Powerup != nullptr;}

	UPROPERTY(BlueprintReadOnly)
	int PlayerIndex = 0;

	UPROPERTY(VisibleAnywhere)
	URaceCarMovementComponent* MoveComp;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<URacePowerup> PowerupClass;

	UPROPERTY()
	URacePowerup* Powerup;
	bool bPowerupActivated = false;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnTeleportParticles();
	
};




