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
	ObjectPool = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();

	soundPlayerSubsystem = GetWorld()->GetSubsystem<USoundLevelPlayerSubsystem>();
	
	RunBehaviorTree(BehaviorTree);

}

void AEnemyAIController::SetIsDead()
{
	bIsDead=true;
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool(TEXT("IsDead"), true);
	OnAiDeadDelegate.Broadcast();
}

void AEnemyAIController::Attack()
{
	bIsAttacking = true;
}

void AEnemyAIController::SetReadyToFight()
{
	bIsReadyToFight = true;
}

