#pragma once
#include "GameFramework/GameMode.h"
#include "RaceGameMode.generated.h"

class URaceOverlayWidget;
class ARaceGameMode;

UCLASS()
class ARaceGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ARaceGameMode();

	UFUNCTION(BlueprintPure, Category = "Race|Game Mode", Meta = (DisplayName="GetRaceGameMode", WorldContext="WorldContext"))
	static ARaceGameMode* Get(UObject* WorldContext);
	
	void StartMatch() override;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<URaceOverlayWidget> OverlayWidgetClass;

	UPROPERTY()
	URaceOverlayWidget* OverlayWidget;
	
};