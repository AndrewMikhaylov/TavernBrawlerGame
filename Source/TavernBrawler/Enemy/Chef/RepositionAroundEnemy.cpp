// Fill out your copyright notice in the Description page of Project Settings.

#include "NavigationSystem.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Chef/RepositionAroundEnemy.h"

URepositionAroundEnemy::URepositionAroundEnemy()
{
	NodeName = TEXT("Find New Position Around Enemy");
}

EBTNodeResult::Type URepositionAroundEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIController->GetWorld());
	FNavLocation Location;
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	NavSys->GetRandomReachablePointInRadius(AIController->CurrentEnemy->GetActorLocation(), RepositionRadius, Location);
	BlackboardComponent->SetValueAsVector(LocationAroundEnemy.SelectedKeyName, Location.Location);
	return EBTNodeResult::Succeeded;
}
