#pragma once
#include "RacePowerup.h"
#include "RaceTeleportPowerup.generated.h"

UCLASS()
class URaceTeleportPowerup : public URacePowerup
{
	GENERATED_BODY()
public:
	void OnPowerupActivated_Implementation() override;
	bool ShouldDeactivate_Implementation() override;
};
