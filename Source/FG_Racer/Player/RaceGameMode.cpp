#include "RaceGameMode.h"
#include "Blueprint/UserWidget.h"
#include "FG_Racer/Game/RaceOverlayWidget.h"

ARaceGameMode::ARaceGameMode()
{
	DefaultPawnClass = nullptr;
}

ARaceGameMode* ARaceGameMode::Get(UObject* WorldContext)
{
	return WorldContext->GetWorld()->GetAuthGameMode<ARaceGameMode>();
}

void ARaceGameMode::StartMatch()
{
	OverlayWidget = NewObject<URaceOverlayWidget>(this, OverlayWidgetClass);
	OverlayWidget->AddToViewport();
	
	Super::StartMatch();
}
