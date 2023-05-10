#include "RaceOverlayWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "RacePlayerStatusWidget.h"

void URaceOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StatusWidgets.SetNum(4);

	UE_LOG(LogTemp, Log, TEXT("URaceOverlayWidget::NativeConstruct()"));
}

void URaceOverlayWidget::AddPlayerStatus(int PlayerIndex)
{
	static FName SlotNames[] = {
		TEXT("Player0Slot"),
		TEXT("Player1Slot"),
		TEXT("Player2Slot"),
		TEXT("Player3Slot"),
	};
	
	URacePlayerStatusWidget* PlayerStatus = NewObject<URacePlayerStatusWidget>(this, PlayerWidgetClass);
	StatusWidgets[PlayerIndex] = PlayerStatus;
	
	SetContentForSlot(SlotNames[PlayerIndex], PlayerStatus);	
}
