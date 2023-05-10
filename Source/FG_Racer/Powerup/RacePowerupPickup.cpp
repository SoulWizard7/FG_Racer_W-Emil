#include "RacePowerupPickup.h"
#include "Components/SphereComponent.h"
#include "RacePowerup.h"
#include "FG_Racer/Player/RaceCar.h"

ARacePowerupPickup::ARacePowerupPickup()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Root);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARacePowerupPickup::BeginOverlapHandle);
}

void ARacePowerupPickup::BeginOverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                            const FHitResult& SweepResult)
{
	
	int RandomIndex = FMath::RandRange(0, PowerupClasses.Num() - 1);
	auto PowerupClass = PowerupClasses[RandomIndex];

	
	
	ARaceCar* Car = Cast<ARaceCar>(OtherActor);
	//if(Car->Powerup != nullptr) return;
	if (!Car->HasEquippedPowerup())
	{
		Car->EquipPowerup(NewObject<URacePowerup>(Car, PowerupClass));
		Destroy(); //destroy the powerup		
	}
}
