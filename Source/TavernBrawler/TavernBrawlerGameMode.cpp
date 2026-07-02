// Copyright Epic Games, Inc. All Rights Reserved.
#include "TavernBrawlerGameMode.h"
#include "TavernBrawlerCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"


ATavernBrawlerGameMode::ATavernBrawlerGameMode()
{
	// stub
}

void ATavernBrawlerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATavernBrawlerGameMode::BeginPlay()
{
	Super::BeginPlay();

	ATavernBrawlerCharacter* playerCharacter = Cast<ATavernBrawlerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	TArray<AActor*> enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIController::StaticClass(), enemies);
	for (auto Enemy : enemies)
	{
		AEnemyAIController* enemyController = Cast<AEnemyAIController>(Enemy);
		enemyController->SetEnemyAI(playerCharacter);
	}
}
