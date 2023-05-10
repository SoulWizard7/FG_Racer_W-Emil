#include "RaceLaser.h"
#include "Components/BoxComponent.h"
#include "FG_Racer/Player/RaceCar.h"

ARaceLaser::ARaceLaser()
{
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = Collision;	
}

void ARaceLaser::BeginPlay()
{
	Super::BeginPlay();
	LaserVelocity = GetActorForwardVector() * 2500.f;
}

void ARaceLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	AddActorWorldOffset(LaserVelocity * DeltaTime, true, &Hit);

	if(Hit.bBlockingHit)
	{
		if(Hit.GetActor() == this) return;

		if(Hit.Actor->IsA<ARaceCar>())
		{
			ARaceCar* HitCar = Cast<ARaceCar>(Hit.Actor);

			if (HitCar->PlayerIndex != OwnerPlayerIndex)
			{
				Hit.Actor->Destroy();
				Destroy();
				return;
			}	
		}
		
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.f, FColor::Orange, Hit.Actor->GetName(), true, FVector2D(1.f));
		//LaserVelocity = LaserVelocity.MirrorByVector(Hit.Normal);
		Destroy();
	}

	timeToDestroy -= DeltaTime;
	if (timeToDestroy < 0.f) Destroy();
}

