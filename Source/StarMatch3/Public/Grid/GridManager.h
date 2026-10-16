// Copyright by Hungnee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

class AStar;

UCLASS()
class STARMATCH3_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Get StarIndex in array
	int GetStarIndexInArray(int _RowIndex, int _ColIndex);
	
	// Star pos in World
	FVector GetStarWorldPosition(int _RowIndex, int _ColIndex);
	
	// Get Star
	AStar* GetStar(int _RowIndex, int _ColIndex);
	
	// Spawn Star
	AStar* SpawnStar(int rowIndex, int colIndex);
	
	UFUNCTION(BlueprintCallable)
	void OnStarClicked(AStar* StarClicked);
	
	bool AreAdjacent(AStar* StarSelected1, AStar* StarSelected2);
	
	// Swap Star
	void SwapStars(AStar* StarSelected1, AStar* StarSelected2);
	
	// Find 3 match Stars
	void FindMatches();
	
	// Destroy 3 match Stars
	void ClearMatches();
	
	// Collapse Column On Board after destroy 3 match Stars
	void CollapseColumnOnBoard(int _ColIndex);
	
	// Resolve loop on board
	UFUNCTION()
	bool ResolveMatches();
	
	void ResolveLoop();
	
	// Star Class
	UPROPERTY(EditDefaultsOnly, Category="Star")
	TSubclassOf<AStar> StarClass;
	
private:	
	// Star 
	TObjectPtr<AStar> Star;
	
	// Star Clicked
	TObjectPtr<AStar> StarSelected;
	
	// Array store Stars
	TArray<AStar*> Stars;
	
	// Array store match 3 Stars
	TArray<AStar*> StarsFound;
	
	// Array store all Stars exist after destroy 
	TArray<AStar*> StarsExist;
	
	/** Num row, col */
	UPROPERTY(EditDefaultsOnly, Category="Size", meta=(AllowPrivateAccess=true))
	int NRow = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="Size", meta=(AllowPrivateAccess=true))
	int NColumn = 0;
	
	// Cell size
	UPROPERTY(EditDefaultsOnly, Category="Size", meta=(AllowPrivateAccess=true))
	int CellSize = 0;
	
	// Star type
	UPROPERTY(EditDefaultsOnly, Category="Star Type", meta=(AllowPrivateAccess=true))
	TArray<UMaterialInterface*> StarMaterials;
	
	// Timer
	FTimerHandle DelayHandle;
};
