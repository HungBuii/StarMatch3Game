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

FVector AGridManager::GetStarWorldPosition(int rowIndex, int colIndex)
{
	return FVector(colIndex * CellSize, 0, rowIndex * CellSize + CellSize);
}

void AGridManager::SpawnStar(int RowIndex, int ColIndex)
{
	FVector SpawnLocation = FVector(0.f, 0.f, 0.f) + GetStarWorldPosition(RowIndex, ColIndex);
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	Star = Cast<AStar>(GetWorld()->SpawnActor<AActor>(StarClass, SpawnLocation, SpawnRotation));
	Star->SetRow(RowIndex);
	Star->SetColumn(ColIndex);
	Star->SetGridManager(this);
	
	if (StarMaterials.Num() > 1)
	{
		int Rand = UKismetMathLibrary::RandomIntegerInRange(0, StarMaterials.Num() - 1);
		Star->SetType(Rand, StarMaterials[Rand]);
	}
}

void AGridManager::OnStarClicked(AStar* StarClicked)
{
	if (StarSelected == nullptr)
	{
		StarSelected = StarClicked;
	}
	else
	{
		if (AreAdjacent(StarClicked, StarSelected))
		{
			SwapStars(StarClicked, StarSelected);
		}
		StarSelected = nullptr;
	}
}

bool AGridManager::AreAdjacent(AStar* StarSelected1, AStar* StarSelected2)
{
	int dRow = abs(StarSelected1->GetRow() - StarSelected2->GetRow());
	int dColumn = abs(StarSelected1->GetColumn() - StarSelected2->GetColumn());
	
	// Same Row							Same Column
	if ( (dRow == 0 && dColumn == 1) || (dRow == 1 && dColumn == 0) )
	{
		return true;
	}
	return false;
}

void AGridManager::SwapStars(AStar* StarSelected1, AStar* StarSelected2)
{
	int TempRow = StarSelected1->GetRow();
	int TempColumn = StarSelected1->GetColumn();
	StarSelected1->SetRow(StarSelected2->GetRow());
	StarSelected1->SetColumn(StarSelected2->GetColumn());
	StarSelected2->SetRow(TempRow);
	StarSelected2->SetColumn(TempColumn);
	
	
	StarSelected1->MoveTo(GetStarWorldPosition(StarSelected1->GetRow(), StarSelected1->GetColumn()));
	StarSelected2->MoveTo(GetStarWorldPosition(StarSelected2->GetRow(), StarSelected2->GetColumn()));
}



