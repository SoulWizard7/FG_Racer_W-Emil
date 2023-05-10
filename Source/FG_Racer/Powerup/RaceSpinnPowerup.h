#pragma once
#include "RacePowerup.h"
#include "RaceSpinnPowerup.generated.h"

class UBoxComponent;

UCLASS()
class URaceSpinnPowerup : public URacePowerup
{
	GENERATED_BODY()

public:
	void Setup_Implementation() override;
	void OnPowerupActivated_Implementation() override;
	bool ShouldDeactivate_Implementation() override;
	void TickActive_Implementation(float DeltaTime) override;

private:
	UPROPERTY()
	UBoxComponent* BoxComponent;

	float BoostTime;
};