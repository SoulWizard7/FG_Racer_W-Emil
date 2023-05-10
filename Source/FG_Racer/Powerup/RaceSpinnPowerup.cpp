#include "RaceSpinnPowerup.h"
#include "Components/BoxComponent.h"

void URaceSpinnPowerup::Setup_Implementation()
{
	BoxComponent = Cast<UBoxComponent>(GetOwner()->GetRootComponent());
}

void URaceSpinnPowerup::OnPowerupActivated_Implementation()
{
	float random = FMath::RandRange(0.1f, 0.5f);
	BoostTime = 0.5f + random;
}

bool URaceSpinnPowerup::ShouldDeactivate_Implementation()
{
	return BoostTime <= 0.f;
}

void URaceSpinnPowerup::TickActive_Implementation(float DeltaTime)
{
	BoostTime -= DeltaTime;
	BoxComponent->AddLocalRotation(FRotator(0.f, 1000.f * DeltaTime, 0.f));
}
