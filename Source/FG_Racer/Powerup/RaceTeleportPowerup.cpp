#include "RaceTeleportPowerup.h"
#include "FG_Racer/Player/RaceCar.h"

void URaceTeleportPowerup::OnPowerupActivated_Implementation()
{	
	auto car = GetOwner();
	car->SpawnTeleportParticles();
	FHitResult Hit;
	car->SetActorLocation(car->GetActorLocation() + car->GetActorForwardVector() * 1000.f, false, &Hit, ETeleportType::TeleportPhysics);
	
}

bool URaceTeleportPowerup::ShouldDeactivate_Implementation()
{
	return true;
}

