// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Brawler/CheckForEnemyAvailability.h"

#include "TavernBrawlerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyAIController.h"

UCheckForEnemyAvailability::UCheckForEnemyAvailability()
{
	NodeName = TEXT("CheckIfEnemyAvailable");
}

EBTNodeResult::Type UCheckForEnemyAvailability::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	ATavernBrawlerCharacter* enemy = Cast<ATavernBrawlerCharacter>(BlackboardComponent->GetValueAsObject(CurrentEnemy.SelectedKeyName));
	AEnemyAIController* thisAI = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (thisAI && enemy)
	{
		if (!thisAI->LineOfSightTo(enemy) || !enemy->CheckIsAlive())
		{
			BlackboardComponent->ClearValue(CurrentEnemy.SelectedKeyName);
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
