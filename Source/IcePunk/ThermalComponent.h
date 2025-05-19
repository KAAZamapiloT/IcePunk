// ThermalComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThermalComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ICEPUNK_API UThermalComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    // Core thermal variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float ThermalLevel = 0.0f; // -100 to +100

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float ThermalRate = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float MinLevel = -100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float MaxLevel = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float ColdThreshold = -70.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float HeatThreshold = 70.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float OptimalLow = -25.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thermal")
    float OptimalHigh = 25.0f;

    // Environmental & player modifiers
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    float ClothingInsulation = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    float HeatResistance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    float WetnessLevel = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    float HydrationLevel = 100.0f;

    // Flags
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsFreezing = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsOverheating = false;

    // Constructor
    UThermalComponent();

    // Main tick function
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Apply temperature influence
    void ApplyEnvironmentalEffects(float EnvironmentTemp);

    // Manual override (like standing near fire)
    UFUNCTION(BlueprintCallable, Category = "Thermal")
    void AdjustThermalLevel(float Amount);

    // Debugging
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void DebugSetTemp(float NewTemp);

protected:
    virtual void BeginPlay() override;

    void UpdateThermalState(float DeltaTime);
    void HandleFreezingState();
    void HandleOverheatingState();
};
