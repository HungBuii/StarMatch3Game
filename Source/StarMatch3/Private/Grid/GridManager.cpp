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
		Stars.Empty();
		
		for (int i = 0; i < NRow; i++)
		{
			for (int j = 0; j < NColumn; j++)
			{
				SpawnStar(i, j);
			}
		}
		
		FindMatches();
		ClearMatches();
	}
}

int AGridManager::GetStarIndexInArray(int _RowIndex, int _ColIndex)
{
	return _RowIndex * NColumn + _ColIndex;
}

FVector AGridManager::GetStarWorldPosition(int _RowIndex, int _ColIndex)
{
	return FVector(_ColIndex * CellSize, 0, _RowIndex * CellSize + CellSize);
}

AStar* AGridManager::GetStar(int _RowIndex, int _ColIndex)
{
	if ( (_RowIndex >= 0 && _RowIndex < NRow) && (_ColIndex >= 0 && _ColIndex < NColumn) )
	{
		return Stars[GetStarIndexInArray(_RowIndex, _ColIndex)];
	}
	
	return nullptr;
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
	
	Stars.Add(Star);
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
	
	Stars[GetStarIndexInArray(StarSelected1->GetRow(), StarSelected1->GetColumn())] = StarSelected1;
	Stars[GetStarIndexInArray(StarSelected2->GetRow(), StarSelected2->GetColumn())] = StarSelected2;
	
	StarSelected1->MoveTo(GetStarWorldPosition(StarSelected1->GetRow(), StarSelected1->GetColumn()));
	StarSelected2->MoveTo(GetStarWorldPosition(StarSelected2->GetRow(), StarSelected2->GetColumn()));
}

void AGridManager::FindMatches()
{
	UE_LOG(LogTemp, Warning, TEXT("StarsNumsArray = %d"), Stars.Num());
	StarsFound.Empty();
	
	// check horizontal
	for (int i = 0; i < NRow; i++)
	{
		for (int j = 0; j < NColumn - 3; j++)
		{
			if (Stars[GetStarIndexInArray(i, j)] != nullptr && 
				Stars[GetStarIndexInArray(i, j + 1)] != nullptr && 
				Stars[GetStarIndexInArray(i, j + 2)] != nullptr && 
				Stars[GetStarIndexInArray(i, j)]->GetType() == Stars[GetStarIndexInArray(i, j + 1)]->GetType() && 
				Stars[GetStarIndexInArray(i, j + 1)]->GetType() == Stars[GetStarIndexInArray(i, j + 2)]->GetType())
			{
				StarsFound.AddUnique(Stars[GetStarIndexInArray(i, j)]);
				StarsFound.AddUnique(Stars[GetStarIndexInArray(i, j + 1)]);
				StarsFound.AddUnique(Stars[GetStarIndexInArray(i, j + 2)]);
				
				// Stars[GetStarIndexInArray(i, j)]->K2_DestroyActor();
				// Stars[GetStarIndexInArray(i, j + 1)]->K2_DestroyActor();
				// Stars[GetStarIndexInArray(i, j + 2)]->K2_DestroyActor();
				
				// Stars.Remove(Stars[GetStarIndexInArray(i, j)]);
				// Stars.Remove(Stars[GetStarIndexInArray(i, j + 1)]);
				// Stars.Remove(Stars[GetStarIndexInArray(i, j + 2)]);
			}
		}
	}
	
	// check vertical
	for (int i = 0; i < NColumn; i++)
	{
		for (int j = 0; j < NRow - 3; j++)
		{
			if (Stars[GetStarIndexInArray(j, i)] != nullptr && 
				Stars[GetStarIndexInArray(j + 1, i)] != nullptr && 
				Stars[GetStarIndexInArray(j + 2, i)] != nullptr && 
				Stars[GetStarIndexInArray(j, i)]->GetType() == 
				Stars[GetStarIndexInArray(j + 1, i)]->GetType() && 
				Stars[GetStarIndexInArray(j + 1, i)]->GetType() == 
				Stars[GetStarIndexInArray(j + 2, i)]->GetType())
			{
				StarsFound.AddUnique(Stars[GetStarIndexInArray(j, i)]);
				StarsFound.AddUnique(Stars[GetStarIndexInArray(j + 1, i)]);
				StarsFound.AddUnique(Stars[GetStarIndexInArray(j + 2, i)]);
				
				// Stars[GetStarIndexInArray(j, i)]->K2_DestroyActor();
				// Stars[GetStarIndexInArray(j + 1, i)]->K2_DestroyActor();
				// Stars[GetStarIndexInArray(j + 2, i)]->K2_DestroyActor();
			}
		}
	}
	
	for (int i = 0; i < StarsFound.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("StarsFound[%d] = %s, %d"), i, *StarsFound[i]->GetName(), StarsFound[i]->GetType());
	}
	
	UE_LOG(LogTemp, Warning, TEXT("StarsNumsArray = %d"), Stars.Num());
	
}

void AGridManager::ClearMatches()
{
	for (int i = 0; i < StarsFound.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stars[%d].Name = %s"), 
			GetStarIndexInArray(StarsFound[i]->GetRow(), StarsFound[i]->GetColumn()),
			*Stars[GetStarIndexInArray(StarsFound[i]->GetRow(), StarsFound[i]->GetColumn())]->GetName()
			);
		Stars[GetStarIndexInArray(StarsFound[i]->GetRow(), StarsFound[i]->GetColumn())]->K2_DestroyActor();
		Stars[GetStarIndexInArray(StarsFound[i]->GetRow(), StarsFound[i]->GetColumn())] = nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("StarsFoundNumsArray = %d"), StarsFound.Num());
	UE_LOG(LogTemp, Warning, TEXT("StarsNumsArray = %d"), Stars.Num());
}



