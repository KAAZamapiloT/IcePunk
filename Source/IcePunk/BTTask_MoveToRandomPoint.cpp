// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToRandomPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "NavigationSystem.h"

UBTTask_MoveToRandomPoint::UBTTask_MoveToRandomPoint()
{
    NodeName = TEXT("Move To Random Point");
    
    // Accept only Vector type for the target location
    TargetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_MoveToRandomPoint, TargetLocationKey));
}

EBTNodeResult::Type UBTTask_MoveToRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Get the current location of the AI
    FVector Origin = AIPawn->GetActorLocation();
    
    // Find a random point within the radius
    FVector RandomLocation = FindRandomReachablePointInRadius(AIController, Origin, Radius, UseNavMesh);
    
    // Set the random location in the blackboard
    BlackboardComp->SetValueAsVector(TargetLocationKey.SelectedKeyName, RandomLocation);
    
    // Move to the random location
    FAIMoveRequest MoveRequest;
    MoveRequest.SetGoalLocation(RandomLocation);
    MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
    
FPathFollowingRequestResult Result =AIController->MoveTo(MoveRequest);
    
    // This task continues running until movement is complete
    return EBTNodeResult::InProgress;
}

void UBTTask_MoveToRandomPoint::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        AIController->StopMovement();
    }
    
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

FVector UBTTask_MoveToRandomPoint::FindRandomReachablePointInRadius(AAIController* AIController, FVector Origin, float InRadius, bool bUseNavMesh) const
{
    if (bUseNavMesh)
    {
        UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIController->GetWorld());
        if (NavSystem)
        {
            FNavLocation RandomPoint;
            if (NavSystem->GetRandomReachablePointInRadius(Origin, InRadius, RandomPoint))
            {
                return RandomPoint.Location;
            }
        }
    }
    
    // If nav mesh failed or is not used, just use a random point in radius
    FVector RandomDirection = FMath::VRand();
    RandomDirection.Z = 0.0f;
    RandomDirection.Normalize();
    
    return Origin + RandomDirection * FMath::RandRange(0.0f, InRadius);
}
