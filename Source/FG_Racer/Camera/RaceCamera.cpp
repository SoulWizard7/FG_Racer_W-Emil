#include "RaceCamera.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "FG_Racer/Game/RaceGameInstance.h"
#include "FG_Racer/Player/RaceCar.h"
#include "Kismet/GameplayStatics.h"

ARaceCamera::ARaceCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);
	
}

void ARaceCamera::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->SetViewTarget(this);

	UE_LOG(LogTemp,Log,TEXT("ARaceCamera::BeginPlay"));
	
	/*
	for(TActorIterator<ARaceCar> It(GetWorld()); It; ++It )
	{
		
	}*/
}

void ARaceCamera::Tick(float DeltaTime)
{
	int NumCars = 0;
	FVector LocationSum = FVector::ZeroVector;
	URaceGameInstance* GameInstance = URaceGameInstance::Get(this);

	for(ARaceCar* Car : GameInstance->Cars)
	{
		LocationSum += Car->GetActorLocation();
		NumCars++;
	}

	if(NumCars == 0) return;
	
	FVector TargetLocation = LocationSum / NumCars;
	FVector Location = GetActorLocation();
	Location = FMath::Lerp(Location, TargetLocation, FollowSpeed * DeltaTime);

	SetActorLocation(Location);
}
