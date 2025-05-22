// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_HealthComponent.h"
#include "DamageComponet.h"
#include "ThermalComponent.h"

// Sets default values for this component's properties
UAC_HealthComponent::UAC_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_HealthComponent::Damage(double Amount)
{
	if (Amount <= 0.0 || (Health.Health <= 0.0 && Health.Armour <= 0.0))
		return;

	// Apply damage to armour first
	double DamageLeft = Amount;

	if (Health.Armour > 0)
	{
		double ArmourDamage = FMath::Min(DamageLeft, Health.Armour);
		Health.Armour -= ArmourDamage;
		DamageLeft -= ArmourDamage;
	}

	// Any damage left applies to health
	if (DamageLeft > 0 && Health.Health > 0)
	{
		Health.Health = FMath::Max(0.0, Health.Health - DamageLeft);
	}
}

void UAC_HealthComponent::Heal(double Amount)
{
	if (Amount <= 0.0 || Health.Health <= 0.0)
		return;

	Health.Health = FMath::Min(Health.MaxHealth, Health.Health + Amount);
}

void UAC_HealthComponent::SetHealth(double NewHealth)
{
}

void UAC_HealthComponent::SetArmour(double NewArmour)
{
}

