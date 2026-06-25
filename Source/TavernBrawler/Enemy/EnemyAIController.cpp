// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAIController.h"

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

