// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/UpdateEnemyPosition.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UUpdateEnemyPosition::UUpdateEnemyPosition()
{
	NodeName = TEXT("Update enemy position");
}

void UUpdateEnemyPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyAIController* thisEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	ATavernBrawlerCharacter* currentEnemyCharacter = thisEnemyController->CurrentEnemy;
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (thisEnemyController && currentEnemyCharacter && BlackboardComponent)
	{
		thisEnemyController->SetFocus(currentEnemyCharacter);
		BlackboardComponent->SetValueAsVector(CurrentEnemyPosition.SelectedKeyName, currentEnemyCharacter->GetActorLocation());
	}
	else
	{
		thisEnemyController->ClearFocus(EAIFocusPriority::Gameplay);
		BlackboardComponent->ClearValue(CurrentEnemyPosition.SelectedKeyName);
	}
	
}
