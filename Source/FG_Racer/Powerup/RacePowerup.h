#pragma once

#include "CoreMinimal.h"
#include "FG_Racer/Player/RaceCar.h"
#include "RacePowerup.generated.h"

class ARaceCar;

UCLASS(Blueprintable)
class URacePowerup : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void Setup();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnPowerupActivated();

	UFUNCTION(BlueprintNativeEvent)
	bool ShouldDeactivate();

	UFUNCTION(BlueprintNativeEvent)
	void TickActive(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	ARaceCar* GetOwner() {return Cast<ARaceCar>(GetOuter());}

	UPROPERTY(EditDefaultsOnly)
	FText PowerupName;
};
