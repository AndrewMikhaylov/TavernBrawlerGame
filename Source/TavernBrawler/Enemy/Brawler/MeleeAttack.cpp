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

	if (AIController && currentEnemy)
	{
		AIController->soundPlayerSubsystem->PlaySoundEffect(AIController->AttackSound, AIController->ThisCharacter->GetActorLocation());
		AIController->SetFocalPoint(currentEnemy->GetActorLocation());
		FVector currentEnemyLocation = currentEnemy->GetActorLocation();
		FVector thisControllerLocation = AIController->ThisCharacter->GetActorLocation();
		float distanceBetweenEnemies = FVector::Distance(currentEnemyLocation, thisControllerLocation);
		FVector AILocation = AIController->GetPawn()->GetActorLocation();
		FVector EnemyLocation = currentEnemy->GetActorLocation();

		FVector AIToEnemy = (EnemyLocation - AILocation).GetSafeNormal();
		FVector AIForward = AIController->GetPawn()->GetActorForwardVector();

		float Dot = FVector::DotProduct(AIForward, AIToEnemy);
		AIController->bIsAttacking = true;
		if (distanceBetweenEnemies<=BlackboardComponent->GetValueAsFloat(AttackRange.SelectedKeyName) && Dot<=1 && Dot>=0.8)
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
