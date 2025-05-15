// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMeshPlacer.generated.h"
UENUM(BlueprintType)
enum class EMeshPlacementShape : uint8
{
    Circle      UMETA(DisplayName = "Circle"),
    Rectangle   UMETA(DisplayName = "Rectangle"),
    Square      UMETA(DisplayName = "Square"),
    Random      UMETA(DisplayName = "Random")
};

UCLASS()
class ICEPUNK_API AAMeshPlacer : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AAMeshPlacer();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Generate mesh placement based on current settings
    UFUNCTION(BlueprintCallable, Category = "Mesh Placement")
    void GenerateMeshPlacement();

    // Clear all placed meshes
    UFUNCTION(BlueprintCallable, Category = "Mesh Placement")
    void ClearPlacement();

    // Regenerate mesh placement with new random seed
    UFUNCTION(BlueprintCallable, Category = "Mesh Placement")
    void RegeneratePlacement();

protected:
    // The static mesh to place
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement")
    UStaticMesh* MeshToPlace;

    // Number of meshes to place
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement", meta = (ClampMin = "1", ClampMax = "1000"))
    int32 NumberOfMeshes = 10;

    // Density of mesh placement (affects spacing)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement", meta = (ClampMin = "0.1", ClampMax = "100.0"))
    float Density = 1.0f;

    // Height at which to place all meshes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement")
    float PlacementHeight = 0.0f;

    // Shape of the placement area
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement")
    EMeshPlacementShape PlacementShape = EMeshPlacementShape::Circle;

    // Radius for circle shape
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement", meta = (EditCondition = "PlacementShape == EMeshPlacementShape::Circle"))
    float CircleRadius = 500.0f;

    // Width for rectangle/square shape
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement", meta = (EditCondition = "PlacementShape == EMeshPlacementShape::Rectangle || PlacementShape == EMeshPlacementShape::Square"))
    float Width = 500.0f;

    // Length for rectangle shape (ignored for square)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement", meta = (EditCondition = "PlacementShape == EMeshPlacementShape::Rectangle"))
    float Length = 1000.0f;

    // Random variation in mesh scale (0.0 = uniform scale, 1.0 = highly varied)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float ScaleVariation = 0.2f;

    // Random rotation of meshes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement")
    bool RandomRotation = true;

    // Random seed for placement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Placement")
    int32 RandomSeed = 0;

#if WITH_EDITOR
    // Allow properties to be updated in the editor
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
    // Array to keep track of spawned mesh components
    UPROPERTY()
    TArray<UStaticMeshComponent*> SpawnedMeshComponents;

    // Helper methods for different placement patterns
    void PlaceInCircle();
    void PlaceInRectangle(bool bIsSquare);
    void PlaceRandomly();

    // Get a random position within the defined shape
    FVector GetRandomPositionInShape() const;
    
    // Apply random variations to the mesh transform
    void ApplyRandomVariations(UStaticMeshComponent* MeshComponent);
};
