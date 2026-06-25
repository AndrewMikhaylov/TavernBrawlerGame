// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Chef/ThrowItemAtEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyAIController.h"


UThrowItemAtEnemy::UThrowItemAtEnemy()
{
	NodeName = TEXT("ThrowItem");
}

EBTNodeResult::Type UThrowItemAtEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}
	ATavernBrawlerCharacter* ThisCharacter = AIController->ThisCharacter;
	ATavernBrawlerCharacter* EnemyCharacter = AIController->CurrentEnemy;
	if (EnemyCharacter->CheckIsAlive())
	{
		AIController->SetFocus(EnemyCharacter);
		AActor* weapon = GetWorld()->SpawnActor(AIController->InteractableItem);
		ThisCharacter->PlayerInventory->EquipAsThrowWeapon(Cast<AInteractableItem>(weapon));
		ThisCharacter->DoThrow();
	}

	AIController->ClearFocus(EAIFocusPriority::Gameplay);

	return EBTNodeResult::Succeeded;
}
