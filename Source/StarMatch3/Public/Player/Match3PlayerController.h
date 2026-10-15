// Copyright by Hungnee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Match3PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STARMATCH3_API AMatch3PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMatch3PlayerController();
	
protected:
	virtual void BeginPlay() override;
};
