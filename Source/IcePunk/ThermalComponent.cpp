// Fill out your copyright notice in the Description page of Project Settings.


#include "ThermalComponent.h"


// Sets default values for this component's properties
UThermalComponent::UThermalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UThermalComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UThermalComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UThermalComponent::ApplyEnvironmentalEffects(float EnvironmentTemp)
{
}

void UThermalComponent::AdjustThermalLevel(float Amount)
{
	ThermalLevel=Amount;
}

void UThermalComponent::DebugSetTemp(float NewTemp)
{
}

void UThermalComponent::UpdateThermalState(float DeltaTime)
{
}

void UThermalComponent::HandleFreezingState()
{
	
}

void UThermalComponent::HandleOverheatingState()
{
	
}

