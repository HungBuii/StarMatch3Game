// Copyright by Hungnee


#include "Player/Match3PlayerController.h"

AMatch3PlayerController::AMatch3PlayerController()
{
}

void AMatch3PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	ClickEventKeys[0] = EKeys::LeftMouseButton;
}
