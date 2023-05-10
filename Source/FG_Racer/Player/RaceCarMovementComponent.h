#pragma once

#include "Components/ActorComponent.h"
#include "RaceCarMovementComponent.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class URaceCarMovementComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	URaceCarMovementComponent();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddForce(const FVector& Force);
	void AddImpulse(const FVector& Impulse);
	
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float Acceleration = 500.f;
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float RollFriction = .8f;
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float GripFriction = 3.8f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float TurnSpeed = 180.f;

	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;
	
	float DriveForwardInput = 0.f;
	float DriveSteerInput = 0.f;
};


