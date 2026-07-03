// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SearchForEnemy.h"

#include "AIController.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

USearchForEnemy::USearchForEnemy()
{
	NodeName = TEXT("Search For Enemy");
}

EBTNodeResult::Type USearchForEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	TArray<AActor*> enemiesAround;
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* thisEnemyAIPawn = AIController->GetPawn();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATavernBrawlerCharacter::StaticClass(), enemiesAround);
	if (enemiesAround.Num() > 0 && AIController->bIsReadyToFight)
	{
		float searchDistance = BlackboardComponent->GetValueAsFloat(SearchRadius.SelectedKeyName);
		for (auto nextEnemy : enemiesAround)
		{
			if (FVector::Distance(nextEnemy->GetActorLocation(), thisEnemyAIPawn->GetActorLocation())<=searchDistance
				&& nextEnemy!=thisEnemyAIPawn)
			{
				AEnemyAIController* thisEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
				thisEnemyController->CurrentEnemy = Cast<ATavernBrawlerCharacter>(nextEnemy);
				BlackboardComponent->SetValueAsObject(CurrentEnemy.SelectedKeyName, nextEnemy);
				return EBTNodeResult::Succeeded;	
			}
		}
	}
	return EBTNodeResult::Failed;
}
