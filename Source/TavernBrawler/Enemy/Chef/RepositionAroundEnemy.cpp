// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Chef/RepositionAroundEnemy.h"

#include "AssetTypeCategories.h"
#include "NavigationSystem.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	FVector enemyPosition = AIController->CurrentEnemy->GetActorLocation();
	FVector thisCharacterPosition = OwnerComp.GetOwner()->GetActorLocation();
	if (RepositionRadius==0)
	{
		NavSys->GetRandomReachablePointInRadius(enemyPosition, FVector::Distance(enemyPosition, thisCharacterPosition), Location);
	}
	else
	{
		NavSys->GetRandomReachablePointInRadius(enemyPosition, RepositionRadius, Location);
	}
	AIController->ClearFocus(EAssetTypeCategories::Gameplay);
	AIController->SetFocalPoint(Location.Location);
	BlackboardComponent->SetValueAsVector(LocationAroundEnemy.SelectedKeyName, Location.Location);
	return EBTNodeResult::Succeeded;
}
