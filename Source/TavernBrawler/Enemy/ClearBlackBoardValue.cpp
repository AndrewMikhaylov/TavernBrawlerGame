// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ClearBlackBoardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UClearBlackBoardValue::UClearBlackBoardValue()
{
	NodeName = TEXT("Clear blackboard value");
}

EBTNodeResult::Type UClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	BlackboardComponent->ClearValue(KeyToClear.SelectedKeyName);
	
	return EBTNodeResult::Succeeded;
}
