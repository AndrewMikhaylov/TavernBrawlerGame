// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Chef/CheckIfEnemyTooClose.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCheckIfEnemyTooClose::UCheckIfEnemyTooClose()
{
	NodeName = TEXT("Check if enemy too close");
}

bool UCheckIfEnemyTooClose::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	AActor* Enemy = Cast<AActor>(Blackboard->GetValueAsObject(CurrentEnemy.SelectedKeyName));
	float Distance = Blackboard->GetValueAsFloat(MaxDistance.SelectedKeyName);
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();

	bool isTooClose = FVector::Distance(Enemy->GetActorLocation(), AIPawn->GetActorLocation()) <= Distance;
	return isTooClose;
}
