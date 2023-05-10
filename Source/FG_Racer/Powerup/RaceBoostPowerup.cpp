#include "RaceBoostPowerup.h"
#include "FG_Racer/Player/RaceCarMovementComponent.h"

void URaceBoostPowerup::Setup_Implementation()
{
	MoveComp = GetOwner()->FindComponentByClass<URaceCarMovementComponent>();
}

void URaceBoostPowerup::OnPowerupActivated_Implementation()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Purple, TEXT("Cpp says hello"));
	BoostTime = 2.f;

	MoveComp->AddImpulse(GetOwner()->GetActorForwardVector() * 1000.f);
}

bool URaceBoostPowerup::ShouldDeactivate_Implementation()
{
	return BoostTime <= 0.f;
}

void URaceBoostPowerup::TickActive_Implementation(float DeltaTime)
{	
	MoveComp->AddForce(GetOwner()->GetActorForwardVector() * 4000.f);
	BoostTime -= DeltaTime;
}
