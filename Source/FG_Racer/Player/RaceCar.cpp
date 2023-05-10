#include "RaceCar.h"
#include "Components/BoxComponent.h"
#include "RaceCarMovementComponent.h"
#include "RaceGameMode.h"
#include "FG_Racer/Game/RaceGameInstance.h"
#include "FG_Racer/Powerup/RacePowerup.h"
#include "FG_Racer/Game/RaceOverlayWidget.h"
#include "FG_Racer/Game/RacePlayerStatusWidget.h"

ARaceCar::ARaceCar()
{
	PrimaryActorTick.bCanEverTick = true;	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = BoxCollision;

	MoveComp = CreateDefaultSubobject<URaceCarMovementComponent>(TEXT("Movement Component"));
}

void ARaceCar::BeginPlay()
{
	Super::BeginPlay();
}

void ARaceCar::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	URaceGameInstance* GameInstance = URaceGameInstance::Get(this);
	GameInstance->Cars.Remove(this);
}

void ARaceCar::SetupPlayerInputComponent(UInputComponent* InputComp)
{
	//Super::SetupPlayerInputComponent(InputComp);

	InputComp->BindAxis(TEXT("Accelerate"), this, &ARaceCar::HandleAccelerateInput);
	InputComp->BindAxis(TEXT("TurnRight"), this, &ARaceCar::HandleTurnRightInput);
	InputComp->BindAction(TEXT("ActivatePowerup"), IE_Pressed, this, &ARaceCar::HandlePowerup);
}

void ARaceCar::Tick(float DeltaTime)
{
	FString msg = FString::Printf(TEXT ("%i"), bPowerupActivated);
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Green, msg, true, FVector2D(4.f));
	
	FColor MSGColor = bPowerupActivated ? FColor::Green : FColor::Red;	

	if(Powerup != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, MSGColor, Powerup->GetClass()->GetName(), true, FVector2D(4.f));

		if(bPowerupActivated)
		{
			Powerup->TickActive(DeltaTime);
			if (Powerup->ShouldDeactivate())
			{
				bPowerupActivated = false;
				//Powerup = nullptr;

				EquipPowerup(nullptr);
			}
		}
	}
}

void ARaceCar::HandlePowerup()
{
	if(Powerup != nullptr && !bPowerupActivated)
	{
		Powerup->OnPowerupActivated();
		bPowerupActivated = true;	
	}
}

void ARaceCar::HandleAccelerateInput(float value)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Magenta, FString::Printf(TEXT("Accelerate: %f"), value));	
	MoveComp->DriveForwardInput = value;
}

void ARaceCar::HandleTurnRightInput(float value)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Blue, FString::Printf(TEXT("TurnRight: %f"), value));
	MoveComp->DriveSteerInput = value;
}

void ARaceCar::EquipPowerup(URacePowerup* NewPowerup)
{
	Powerup = NewPowerup;

	if(Powerup != nullptr) Powerup->Setup();
	
	auto* GameMode = ARaceGameMode::Get(this);
	auto* StatusWidget = GameMode->OverlayWidget->StatusWidgets[PlayerIndex];

	StatusWidget->SetEquippedPowerup(NewPowerup);
}



