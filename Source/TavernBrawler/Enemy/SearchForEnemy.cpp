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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATavernBrawlerCharacter::StaticClass(), enemiesAround);
	if (enemiesAround.Num() > 0)
	{
		float searchDistance = BlackboardComponent->GetValueAsFloat(SearchRadius.SelectedKeyName);
		for (auto nextEnemy : enemiesAround)
		{
			if (FVector::Distance(nextEnemy->GetActorLocation(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation())<=searchDistance)
			{
				AEnemyAIController* thisEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
				thisEnemyController->CurrentEnemy = Cast<ATavernBrawlerCharacter>(nextEnemy);
				return EBTNodeResult::Succeeded;	
			}
		}
	}
	return EBTNodeResult::Failed;
}
