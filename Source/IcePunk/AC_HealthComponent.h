// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_HealthComponent.generated.h"

UENUM()
enum EHealthEffect
{
	EHS_Invincible
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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
   TArray<EHealthEffect>CurrentEffect;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ICEPUNK_API UAC_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_HealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	

		
	
};
