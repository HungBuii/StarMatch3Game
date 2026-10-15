// Copyright by Hungnee


#include "Star/Star.h"

// Sets default values
AStar::AStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStar::BeginPlay()
{
	Super::BeginPlay();
	
}

int AStar::GetRow()
{
	return RowIndex;
}

int AStar::GetColumn()
{
	return ColumnIndex;
}

void AStar::SetRow(int row)
{
	RowIndex = row;
}

void AStar::SetColumn(int column)
{
	ColumnIndex = column;
}

