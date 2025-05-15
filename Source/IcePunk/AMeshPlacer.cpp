#include "AMeshPlacer.h"

// Sets default values
AAMeshPlacer::AAMeshPlacer()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAMeshPlacer::BeginPlay()
{
    Super::BeginPlay();
    
    // Generate mesh placement when game starts
    GenerateMeshPlacement();
}

// Called every frame
void AAMeshPlacer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAMeshPlacer::GenerateMeshPlacement()
{
    // Clear existing placement first
    ClearPlacement();

    // Check if we have a valid mesh to place
    if (!MeshToPlace)
    {
        UE_LOG(LogTemp, Warning, TEXT("No mesh assigned for placement!"));
        return;
    }

    // Set the random seed
    FMath::RandInit(RandomSeed);

    // Choose placement strategy based on the selected shape
    switch (PlacementShape)
    {
    case EMeshPlacementShape::Circle:
        PlaceInCircle();
        break;
    case EMeshPlacementShape::Rectangle:
        PlaceInRectangle(false);
        break;
    case EMeshPlacementShape::Square:
        PlaceInRectangle(true);
        break;
    case EMeshPlacementShape::Random:
        PlaceRandomly();
        break;
    default:
        PlaceInCircle();
        break;
    }
}

void AAMeshPlacer::ClearPlacement()
{
    // Destroy all spawned mesh components
    for (UStaticMeshComponent* MeshComp : SpawnedMeshComponents)
    {
        if (MeshComp)
        {
            MeshComp->DestroyComponent();
        }
    }

    // Clear the array
    SpawnedMeshComponents.Empty();
}

void AAMeshPlacer::RegeneratePlacement()
{
    // Change the random seed
    RandomSeed = FMath::Rand();
    GenerateMeshPlacement();
}

void AAMeshPlacer::PlaceInCircle()
{
    for (int32 i = 0; i < NumberOfMeshes; ++i)
    {
        // Calculate a random angle and distance within the circle
        float Angle = FMath::RandRange(0.0f, 2.0f * PI);
        // Use square root to ensure uniform distribution within the circle
        float Distance = FMath::Sqrt(FMath::RandRange(0.0f, 1.0f)) * CircleRadius;
        
        // Adjust distance by density (higher density = closer meshes)
        Distance *= (1.0f / FMath::Max(0.1f, Density));
        
        // Calculate position
        float X = Distance * FMath::Cos(Angle);
        float Y = Distance * FMath::Sin(Angle);
        
        // Create a new static mesh component
        FString CompName = FString::Printf(TEXT("Mesh_%d"), i);
        UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this, FName(*CompName));
        MeshComp->SetStaticMesh(MeshToPlace);
        MeshComp->SetupAttachment(RootComponent);
        MeshComp->RegisterComponent();
        
        // Position the mesh
        FVector ActorLocation = GetActorLocation();
        FVector PlacementLocation = ActorLocation + FVector(X, Y, PlacementHeight);
        MeshComp->SetWorldLocation(PlacementLocation);
        
        // Apply random variations
        ApplyRandomVariations(MeshComp);
        
        // Add to our tracking array
        SpawnedMeshComponents.Add(MeshComp);
    }
}

void AAMeshPlacer::PlaceInRectangle(bool bIsSquare)
{
    float RectangleLength = bIsSquare ? Width : Length;
    
    for (int32 i = 0; i < NumberOfMeshes; ++i)
    {
        // Calculate random position within rectangle/square
        float X = FMath::RandRange(-Width / 2.0f, Width / 2.0f);
        float Y = FMath::RandRange(-RectangleLength / 2.0f, RectangleLength / 2.0f);
        
        // Adjust dimensions by density
        X *= (1.0f / FMath::Max(0.1f, Density));
        Y *= (1.0f / FMath::Max(0.1f, Density));
        
        // Create a new static mesh component
        FString CompName = FString::Printf(TEXT("Mesh_%d"), i);
        UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this, FName(*CompName));
        MeshComp->SetStaticMesh(MeshToPlace);
        MeshComp->SetupAttachment(RootComponent);
        MeshComp->RegisterComponent();
        
        // Position the mesh
        FVector ActorLocation = GetActorLocation();
        FVector PlacementLocation = ActorLocation + FVector(X, Y, PlacementHeight);
        MeshComp->SetWorldLocation(PlacementLocation);
        
        // Apply random variations
        ApplyRandomVariations(MeshComp);
        
        // Add to our tracking array
        SpawnedMeshComponents.Add(MeshComp);
    }
}

void AAMeshPlacer::PlaceRandomly()
{
    // For random placement, we'll use the largest dimension as our boundary
    float MaxDimension = FMath::Max(FMath::Max(Width, Length), CircleRadius * 2.0f);
    
    for (int32 i = 0; i < NumberOfMeshes; ++i)
    {
        // Get a random position within our shape
        FVector RandomPosition = GetRandomPositionInShape();
        
        // Create a new static mesh component
        FString CompName = FString::Printf(TEXT("Mesh_%d"), i);
        UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this, FName(*CompName));
        MeshComp->SetStaticMesh(MeshToPlace);
        MeshComp->SetupAttachment(RootComponent);
        MeshComp->RegisterComponent();
        
        // Position the mesh
        FVector ActorLocation = GetActorLocation();
        FVector PlacementLocation = ActorLocation + FVector(RandomPosition.X, RandomPosition.Y, PlacementHeight);
        MeshComp->SetWorldLocation(PlacementLocation);
        
        // Apply random variations
        ApplyRandomVariations(MeshComp);
        
        // Add to our tracking array
        SpawnedMeshComponents.Add(MeshComp);
    }
}

FVector AAMeshPlacer::GetRandomPositionInShape() const
{
    FVector RandomPosition;
    
    switch (PlacementShape)
    {
    case EMeshPlacementShape::Circle:
        {
            // Same as circle placement logic
            float Angle = FMath::RandRange(0.0f, 2.0f * PI);
            float Distance = FMath::Sqrt(FMath::RandRange(0.0f, 1.0f)) * CircleRadius;
            Distance *= (1.0f / FMath::Max(0.1f, Density));
            RandomPosition.X = Distance * FMath::Cos(Angle);
            RandomPosition.Y = Distance * FMath::Sin(Angle);
            RandomPosition.Z = 0.0f;
        }
        break;
    case EMeshPlacementShape::Rectangle:
        {
            // Rectangle placement
            float X = FMath::RandRange(-Width / 2.0f, Width / 2.0f);
            float Y = FMath::RandRange(-Length / 2.0f, Length / 2.0f);
            X *= (1.0f / FMath::Max(0.1f, Density));
            Y *= (1.0f / FMath::Max(0.1f, Density));
            RandomPosition = FVector(X, Y, 0.0f);
        }
        break;
    case EMeshPlacementShape::Square:
        {
            // Square placement
            float X = FMath::RandRange(-Width / 2.0f, Width / 2.0f);
            float Y = FMath::RandRange(-Width / 2.0f, Width / 2.0f);
            X *= (1.0f / FMath::Max(0.1f, Density));
            Y *= (1.0f / FMath::Max(0.1f, Density));
            RandomPosition = FVector(X, Y, 0.0f);
        }
        break;
    case EMeshPlacementShape::Random:
        {
            // Truly random in a big square
            float MaxRange = FMath::Max(CircleRadius, FMath::Max(Width, Length)) / 2.0f;
            float X = FMath::RandRange(-MaxRange, MaxRange);
            float Y = FMath::RandRange(-MaxRange, MaxRange);
            X *= (1.0f / FMath::Max(0.1f, Density));
            Y *= (1.0f / FMath::Max(0.1f, Density));
            RandomPosition = FVector(X, Y, 0.0f);
        }
        break;
    default:
        RandomPosition = FVector::ZeroVector;
        break;
    }
    
    return RandomPosition;
}

void AAMeshPlacer::ApplyRandomVariations(UStaticMeshComponent* MeshComponent)
{
    if (!MeshComponent)
        return;
    
    // Apply random scale if variation is enabled
    if (ScaleVariation > 0.0f)
    {
        float BaseScale = 1.0f;
        float ScaleModifier = FMath::RandRange(1.0f - ScaleVariation, 1.0f + ScaleVariation);
        MeshComponent->SetWorldScale3D(FVector(BaseScale * ScaleModifier));
    }
    
    // Apply random rotation if enabled
    if (RandomRotation)
    {
        // Random rotation around Z axis for natural variation
        float YawRotation = FMath::RandRange(0.0f, 360.0f);
        MeshComponent->SetWorldRotation(FRotator(0.0f, YawRotation, 0.0f));
    }
}

#if WITH_EDITOR
void AAMeshPlacer::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Auto-update in editor when properties change
    if (PropertyChangedEvent.Property && !GIsPlayInEditorWorld)
    {
        // For efficiency, you could check specific properties that require regeneration
        GenerateMeshPlacement();
    }
}
#endif
