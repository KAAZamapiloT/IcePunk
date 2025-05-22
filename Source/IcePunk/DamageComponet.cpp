// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponet.h"


// Sets default values for this component's properties
UDamageComponet::UDamageComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageComponet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageComponet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageComponet::ImpartDamage()
{
}

void UDamageComponet::TimedDamage()
{
}

