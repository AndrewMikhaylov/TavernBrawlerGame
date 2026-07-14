// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Brawler/MeleeAttack.h"

#include "TavernBrawlerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyAIController.h"
#include "Engine/DamageEvents.h"

class AEnemyAIController;

UMeleeAttack::UMeleeAttack()
{
	NodeName = TEXT("DoMeleeAttack");
}

EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	ATavernBrawlerCharacter* currentEnemy = Cast<ATavernBrawlerCharacter>(BlackboardComponent->GetValueAsObject(CurrentEnemy.SelectedKeyName));
	AEnemyAIController* thisEnemyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	
	if (thisEnemyController && currentEnemy)
	{
		thisEnemyController->SetFocalPoint(currentEnemy->GetActorLocation());
		FVector currentEnemyLocation = currentEnemy->GetActorLocation();
		FVector thisControllerLocation = thisEnemyController->ThisCharacter->GetActorLocation();
		float distanceBetweenEnemies = FVector::Distance(currentEnemyLocation, thisControllerLocation);
		FVector AIForward = thisEnemyController->GetPawn()->GetActorForwardVector();
		FVector AIToEnemy = (currentEnemyLocation - thisEnemyController->GetPawn()->GetActorForwardVector()).GetSafeNormal();
		float angle = FVector::DotProduct(AIForward, AIToEnemy);
		thisEnemyController->bIsAttacking = true;
		if (distanceBetweenEnemies<=BlackboardComponent->GetValueAsFloat(AttackRange.SelectedKeyName) && angle<=1 && angle>=0.6)
		{
			FPointDamageEvent DamageEvent;
			currentEnemy->TakeDamage(BlackboardComponent->GetValueAsFloat(AttackDamage.SelectedKeyName),
				DamageEvent,
				thisEnemyController,
				thisEnemyController->ThisCharacter);
		}
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
