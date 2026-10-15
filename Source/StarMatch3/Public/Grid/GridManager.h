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
	// Star pos in World
	FVector GetStarWorldPosition(int rowIndex, int colIndex);
	
	void SpawnStar(int rowIndex, int colIndex);
	
	UFUNCTION(BlueprintCallable)
	void OnStarClicked(AStar* StarClicked);
	
	bool AreAdjacent(AStar* StarSelected1, AStar* StarSelected2);
	
	void SwapStars(AStar* StarSelected1, AStar* StarSelected2);
	
	// Star Class
	UPROPERTY(EditDefaultsOnly, Category="Star")
	TSubclassOf<AStar> StarClass;
	
private:	
	// Star 
	TObjectPtr<AStar> Star;
	
	// Star Clicked
	TObjectPtr<AStar> StarSelected;
	
	/** Num row, col */
	UPROPERTY(EditDefaultsOnly, Category="Size", meta=(AllowPrivateAccess=true))
	int NRow = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="Size", meta=(AllowPrivateAccess=true))
	int NColumn = 0;
	
	// Cell size
	UPROPERTY(EditDefaultsOnly, Category="Size", meta=(AllowPrivateAccess=true))
	int CellSize = 0;
	
	/** Star type */
	UPROPERTY(EditDefaultsOnly, Category="Star Type", meta=(AllowPrivateAccess=true))
	TArray<UMaterialInterface*> StarMaterials;
};
