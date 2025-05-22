// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damageable.h"
#include "AC_HealthComponent.generated.h"


//  I WANT TO DO ALL HEALTH RELATED MANAGEMENT IN THIS HEALTH COMPONENT CLASS
// BUT THERE ARE DIFFRENT TYPES OF DAMAGE THIS GAME WILL KEEP THERMAL AND OTHER PHYSICAL DAMAGE IN DIFFRENT CLASSES
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	EDT_None           UMETA(DisplayName = "None"),
	EDT_Point          UMETA(DisplayName = "Point"),
	EDT_Fire           UMETA(DisplayName = "Fire"),
	EDT_Ice            UMETA(DisplayName = "Ice"),
	EDT_Electric       UMETA(DisplayName = "Electric"),
	EDT_Explosion      UMETA(DisplayName = "Explosion"),
	EDT_Poison         UMETA(DisplayName = "Poison"),
	EDT_Fall           UMETA(DisplayName = "Fall"),
	EDT_Environmental  UMETA(DisplayName = "Environmental"),
	// Extend as needed
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	EDS_None       UMETA(DisplayName = "None"),
	EDS_Immune     UMETA(DisplayName = "Immune"),
	EDS_Absorb     UMETA(DisplayName = "Absorb"),
	EDS_Resist     UMETA(DisplayName = "Resist"),
	EDS_Normal     UMETA(DisplayName = "Normal"),
	EDS_Weak       UMETA(DisplayName = "Weak"),
	// Extend as needed
};
USTRUCT(BlueprintType)
struct FAC_Health
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    double Health;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    double Armour;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    double MaxHealth;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    double MaxArmour;
	
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ICEPUNK_API UAC_HealthComponent : public UActorComponent ,public IDamageable 
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_HealthComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	class UThermalComponent* Thermal;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	struct FAC_Health Health;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
   UFUNCTION(BlueprintCallable, Category = "Damage")
	void Damage(double Amount) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void Heal(double Amount) override;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(double NewHealth);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetArmour(double NewArmour);
	
};