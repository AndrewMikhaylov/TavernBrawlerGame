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
	AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	
	AIController->soundPlayerSubsystem->PlaySoundEffect(AIController->AttackSound, AIController->ThisCharacter->GetActorLocation());

	if (AIController && currentEnemy)
	{
		AIController->SetFocalPoint(currentEnemy->GetActorLocation());
		FVector currentEnemyLocation = currentEnemy->GetActorLocation();
		FVector thisControllerLocation = AIController->ThisCharacter->GetActorLocation();
		float distanceBetweenEnemies = FVector::Distance(currentEnemyLocation, thisControllerLocation);
		FVector AIForward = AIController->GetPawn()->GetActorForwardVector();
		FVector AIToEnemy = (currentEnemyLocation - AIController->GetPawn()->GetActorForwardVector()).GetSafeNormal();
		float angle = FVector::DotProduct(AIForward, AIToEnemy);
		AIController->bIsAttacking = true;
		if (distanceBetweenEnemies<=BlackboardComponent->GetValueAsFloat(AttackRange.SelectedKeyName) && angle<=1 && angle>=0.6)
		{
			FPointDamageEvent DamageEvent;
			currentEnemy->TakeDamage(BlackboardComponent->GetValueAsFloat(AttackDamage.SelectedKeyName),
				DamageEvent,
				AIController,
				AIController->ThisCharacter);
		}
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
