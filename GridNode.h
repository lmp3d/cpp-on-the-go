// Data Structure to store a location and Boolean value

USTRUCT(EditAnywhere, BlueprintReadWrite)
struct GridNode
{
 USTRUCT_GENERATED_BODY()

 bool isWall;

 FVector location;

 GridNode()
 {
  isWall = true;
  location = FVector(0.0F,0.0F,0.0F);
 }
}
