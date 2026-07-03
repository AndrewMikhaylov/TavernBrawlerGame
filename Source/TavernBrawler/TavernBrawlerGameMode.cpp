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

void ATavernBrawlerGameMode::BeginFight()
{
	if (!bFightStarted)
	{
		for (auto enemy : Enemies)
		{
			AEnemyAIController* enemyController = Cast<AEnemyAIController>(enemy);
			enemyController->SetReadyToFight();
		}
		for (auto tavernFighter : TavernFighters)
		{
			ATavernBrawlerCharacter* tavernCharacter = Cast<ATavernBrawlerCharacter>(tavernFighter);
			tavernCharacter->OnFirstDamageTaken.RemoveAll(this);
		}
		bFightStarted = true;
	}
}

void ATavernBrawlerGameMode::BeginPlay()
{
	Super::BeginPlay();

	ATavernBrawlerCharacter* playerCharacter = Cast<ATavernBrawlerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATavernBrawlerCharacter::StaticClass(), TavernFighters);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIController::StaticClass(), Enemies);
	for (auto Enemy : Enemies)
	{
		AEnemyAIController* enemyController = Cast<AEnemyAIController>(Enemy);
		enemyController->SetEnemyAI(playerCharacter);
	}

	for (auto tavernFighter : TavernFighters)
	{
		ATavernBrawlerCharacter* tavernCharacter = Cast<ATavernBrawlerCharacter>(tavernFighter);
		tavernCharacter->OnFirstDamageTaken.AddUObject(this, &ATavernBrawlerGameMode::BeginFight);
	}
}
