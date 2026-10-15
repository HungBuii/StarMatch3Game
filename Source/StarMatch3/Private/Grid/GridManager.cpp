// Copyright by Hungnee


#include "Grid/GridManager.h"

#include "Kismet/KismetMathLibrary.h"
#include "Star/Star.h"

// Sets default values
AGridManager::AGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (StarClass)
	{
		for (int i = 0; i < NRow; i++)
		{
			for (int j = 0; j < NColumn; j++)
			{
				SpawnStar(i, j);
			}
		}
		
	}
}

FVector AGridManager::GetWorldPosition(int rowIndex, int colIndex)
{
	return FVector(colIndex * CellSize, 0, rowIndex * CellSize + CellSize);
}

void AGridManager::SpawnStar(int rowIndex, int colIndex)
{
	FVector SpawnLocation = FVector(0.f, 0.f, 0.f) + GetWorldPosition(rowIndex, colIndex);
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	Star = Cast<AStar>(GetWorld()->SpawnActor<AActor>(StarClass, SpawnLocation, SpawnRotation));
	Star->SetRow(rowIndex);
	Star->SetColumn(colIndex);
	
	if (StarMaterials.Num() > 1)
	{
		int Rand = UKismetMathLibrary::RandomIntegerInRange(0, StarMaterials.Num() - 1);
		Star->SetType(Rand, StarMaterials[Rand]);
	}
}



