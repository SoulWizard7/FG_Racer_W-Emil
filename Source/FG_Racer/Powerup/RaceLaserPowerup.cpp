#include "RaceLaserPowerup.h"
#include "RaceLaser.h"

void URaceLaserPowerup::OnPowerupActivated_Implementation()
{
	for(int i = 0; i < 10; i++)
	{
		float angle = -359.f;
		FTransform SpawnTransform = GetOwner()->GetActorTransform();
		SpawnTransform += FTransform(FRotator(0,   angle + i * 71.f, 0 ));
		
		auto laser = GetWorld()->SpawnActor(LaserClass, &SpawnTransform);
		ARaceLaser* l = Cast<ARaceLaser>(laser);
		l->OwnerPlayerIndex = GetOwner()->PlayerIndex;
		
		
		//laser->AddActorLocalRotation(FRotator(0, 36.f * i,0));
		
	}
}
