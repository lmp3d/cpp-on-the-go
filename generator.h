// Leif Peterson 2016

#pragma once

#include "GameFramework/Actor.h"
#include "WallNode.h"
#include "ACaveGenerator.generated.h"


/*USTRUCT(BlueprintType)
struct FGridNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool isWall;

	UPROPERTY()
	FVector Location;

	void SetIsWall(bool NewBoolean) { isWall = NewBoolean; }

	void SetLocation(FVector NewLocation) { Location = NewLocation;  }

	bool GetIsWall() { return isWall; }

	FVector GetLocation() { return Location; }

	FGridNode()
	{
		isWall = true;
		Location = FVector(0, 0, 0);
	}

};
*/

USTRUCT(BlueprintType)
struct FGridNodeRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings", meta = (ClampMin = "0", UIMin = "0"))
	TArray<WallNode*> Width;

	void AddNewWidth() { Width.Add(NULL); }

	FGridNodeRow(){}

};

USTRUCT(BlueprintType)
struct FGridNodeArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings", meta = (ClampMin = "0", UIMin = "0"))
	TArray<FGridNodeRow> Height;

	void AddNewHeight() { Height.Add(FGridNodeRow()); }

	void AddUninitialized(const int32 GridHeight, const int32 GridWidth)
	{
		// Create Rows For Height
		for (int32 h = 0; h < GridHeight; h++)
		{
			AddNewHeight();
		}
		// Create Width Nodes
		for (int32 h = 0; h < GridHeight; h++)
		{
			for (int32 w = 0; w < GridWidth; w++)
			{
				Height[h].AddNewWidth();
			}
		}

	}

	void Clear()
	{
		if (Height.Num() <= 0) return;

		// Destroy All Nodes
		const int32 HeightTotal = Height.Num();
		const int32 WidthTotal = Height[0].Width.Num();

		for (int32 h = 0; h < HeightTotal; h++)
		{
			for (int32 w = 0; w < WidthTotal; w++)
			{
				if (Height[h].Width[w] && Height[h].Width[w]->IsValidLowLevel())
				{
					Height[h].Width[w]->Destroy();
				}
			}
		}

		// Empty
		for (int32 h = 0; h < Height.Num(); h++)
		{
			Height[h].Width.Empty();
		}
		Height.Empty();
	}

	FGridNodeArray(){}
};

UCLASS()
class PROCTEST_API AACaveGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACaveGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	uint8 RandomFillPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (ClampMin ="0", UIMin = "0"))
	int32 Seed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings")
	bool useRandomSeed;

	UPROPERTY()
	FGridNodeArray NodeGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (ClampMin = "0", UIMin = "0"))
	int32 MapWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Settings", meta = (ClampMin = "0", UIMin = "0"))
	int32 MapHeight;

private:
	FDateTime DateAndTime;
	uint8 CaveMap [100][100] = {0};

	uint32 safeSeed;

	// Generate the Map
	void GenerateMap();
	void RandomFillMap();
	void DrawDebug();
	
};
