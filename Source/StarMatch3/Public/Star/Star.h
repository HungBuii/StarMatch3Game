// Copyright by Hungnee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Star.generated.h"

UCLASS()
class STARMATCH3_API AStar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/** row, col Getter/Setter */
	int GetRow();
	int GetColumn();
	void SetRow(int row);
	void SetColumn(int column);
	
	// Set Material
	UFUNCTION(BlueprintImplementableEvent)
	void SetType(int type, UMaterialInterface* material);
	
private:
	/** row, col index */
	UPROPERTY(VisibleAnywhere, Category="Index", meta=(AllowPrivateAccess=true))
	int RowIndex = 0;
	
	UPROPERTY(VisibleAnywhere, Category="Index", meta=(AllowPrivateAccess=true))
	int ColumnIndex = 0;
	
	// num type material
	UPROPERTY(BlueprintReadWrite, Category="Material", meta=(AllowPrivateAccess=true))
	int NumType = 0;
};
