// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CheckIfThisEnemyIsAlive.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCheckIfThisEnemyIsAlive::UCheckIfThisEnemyIsAlive()
{
	NodeName = TEXT("Check if this enemy is alive");
}

EBTNodeResult::Type UCheckIfThisEnemyIsAlive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AIController->ThisCharacter->CheckIsAlive();
	if (!AIController->ThisCharacter->CheckIsAlive())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsAlive.SelectedKeyName, false);
	}
	return EBTNodeResult::Succeeded;
}
