
#include "RaceCarMovementComponent.h"

URaceCarMovementComponent::URaceCarMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URaceCarMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	AActor* Owner = GetOwner();

	//Acceleration
	Velocity += Owner->GetActorForwardVector() * Acceleration * DriveForwardInput * DeltaTime;

	//Friction
	FVector RollingVelocity = Velocity.ProjectOnTo(Owner->GetActorForwardVector());
	FVector GripVelocity = Velocity - RollingVelocity;

	RollingVelocity -= RollingVelocity * RollFriction * DeltaTime;
	GripVelocity -= GripVelocity * GripFriction * DeltaTime;
	Velocity = RollingVelocity + GripVelocity;

	//apply movement
	float RemainingTime = DeltaTime;
	int Iterations = 0;
	
	while(RemainingTime> 0.f && ++Iterations < 10)
	{
		FHitResult Hit;	
		Owner->AddActorWorldOffset(Velocity * RemainingTime, true, &Hit);
		
		//if we hit something
		if (Hit.bBlockingHit)
		{
			if (Hit.bStartPenetrating)
			{
				// Depenetration
				Owner->AddActorWorldOffset(Hit.Normal * (Hit.PenetrationDepth + 0.1f));
			}
			else
			{
				Velocity = FVector::VectorPlaneProject(Velocity, Hit.Normal);
				RemainingTime -= RemainingTime * Hit.Time;
			}
		}
		else
		{
			break;
		}
	}

	if (Iterations == 10)
	{
		UE_LOG(LogTemp, Log, TEXT("WE ARE STUCK"));
	}

	float Speed = FVector::DotProduct(Velocity, Owner->GetActorForwardVector());
	Owner->AddActorLocalRotation(FRotator(0.f, DriveSteerInput * TurnSpeed * Speed * DeltaTime, 0.f));	
}

void URaceCarMovementComponent::AddForce(const FVector& Force)
{	
	Velocity += Force * GetWorld()->GetDeltaSeconds();
}

void URaceCarMovementComponent::AddImpulse(const FVector& Impulse)
{
	Velocity += Impulse;
}
