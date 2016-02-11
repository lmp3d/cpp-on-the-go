// Leif Peterson 2016

#include "ProcTest.h"
#include "ACaveGenerator.h"
#include "DrawDebugHelpers.h"


// Sets default values
AACaveGenerator::AACaveGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Defaults
	RandomFillPercentage = 50;
	useRandomSeed = false;
	Seed = 10;
	safeSeed = uint32(Seed);
	MapWidth = 100;
	MapHeight = 100;

	// Init Grid
	NodeGrid.Clear();
	NodeGrid.AddUninitialized(MapHeight, MapWidth);

}

// Called when the game starts or when spawned
void AACaveGenerator::BeginPlay()
{
	Super::BeginPlay();

	GenerateMap();
	DrawDebug();
	
}

// Called every frame
void AACaveGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AACaveGenerator::GenerateMap()
{
	RandomFillMap();
}

void AACaveGenerator::RandomFillMap() 
{	
	if (useRandomSeed) {
		uint64 rawtime = DateAndTime.ToUnixTimestamp();
		safeSeed = uint32 (rawtime);
	}

	FRandomStream psuRandom = FRandomStream(Seed);
	for (uint8 x = 0; x < 100; x++) {
		for (uint8 y = 0; y < 100; y++) {
			CaveMap[x][y] = (FMath::RandRange(0, 100) < RandomFillPercentage) ? 1 : 0;
			// iterate the seed
			uint32 cSeed = psuRandom.GetCurrentSeed();
			uint32 nSeed = (cSeed * 3) + 1;
			psuRandom.Initialize(nSeed);
		}
	}

}

void AACaveGenerator::DrawDebug()
{
	if (CaveMap != NULL) {
		for (uint8 x = 0; x < 100; x++) {
			for (uint8 y = 0; y < 100; y++) {
				FVector position = FVector(x * 100.0F, y * 100.0F, 0.0F);
				if (CaveMap[x][y] == 1) { DrawDebugPoint(GetWorld(), position, 5.0F, FColor(255,0,0), false, 60.0F, 0); }
				else { DrawDebugPoint(GetWorld(), position, 5.0F, FColor(0,0,255), false, 60.0F, 0); }
			}
		}
	}
}
