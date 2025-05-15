// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToRandomPoint.generated.h"

/**
 * 
 */
UCLASS()
class ICEPUNK_API UBTTask_MoveToRandomPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MoveToRandomPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Task")
	float Radius = 500.0f;
	
	UPROPERTY(EditAnywhere, Category = "Task")
	bool UseNavMesh = true;
	
	UPROPERTY(EditAnywhere, Category = "Task")
	float AcceptanceRadius = 50.0f;
	
	// Blackboard key to store the target location
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetLocationKey;
	
private:
	FVector FindRandomReachablePointInRadius(AAIController* AIController, FVector Origin, float InRadius, bool bUseNavMesh) const;
};
