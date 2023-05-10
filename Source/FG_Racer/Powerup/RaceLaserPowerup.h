#pragma once
#include "RacePowerup.h"
#include "RaceLaserPowerup.generated.h"

class ARaceLaser;

UCLASS(Abstract)
class URaceLaserPowerup : public URacePowerup
{
	GENERATED_BODY()
public:
	void OnPowerupActivated_Implementation() override;

	UPROPERTY(EditDefaultsOnly, Category = Poopa)
	TSubclassOf<ARaceLaser> LaserClass;
	
};