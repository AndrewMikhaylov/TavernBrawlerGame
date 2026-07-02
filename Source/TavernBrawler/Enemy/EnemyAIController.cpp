// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyAIController::SetEnemyAI(ATavernBrawlerCharacter* playerCharacter)
{
	Player = playerCharacter;
	ThisCharacter = Cast<ATavernBrawlerCharacter>(GetPawn());
	RunBehaviorTree(BehaviorTree);

}

void AEnemyAIController::SetIsDead()
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool(TEXT("IsAlive"), false);
}

void AEnemyAIController::Attack()
{
	bIsAttacking = true;
}

