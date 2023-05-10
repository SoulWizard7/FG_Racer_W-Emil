#pragma once

#include "GameFramework/Actor.h"
#include "RaceLaser.generated.h"

class UBoxComponent;

UCLASS()
class ARaceLaser : public AActor
{
	GENERATED_BODY()
public:

	ARaceLaser();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collision;

	UPROPERTY()
	FVector LaserVelocity;

	UPROPERTY()
	int OwnerPlayerIndex = -1;

	float timeToDestroy = 4.f;
	
};