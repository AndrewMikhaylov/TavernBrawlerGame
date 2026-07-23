// Copyright Epic Games, Inc. All Rights Reserved.
#include "TavernBrawlerGameMode.h"
#include "TavernBrawlerCharacter.h"
#include "TavernBrawlerPlayerController.h"
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

	playerCharacter = Cast<ATavernBrawlerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	playerController = GetWorld()->GetFirstPlayerController();
	
	playerCharacter->OnPlayerDead.AddUObject(this, &ATavernBrawlerGameMode::SetGameLost);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATavernBrawlerCharacter::StaticClass(), TavernFighters);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIController::StaticClass(), Enemies);
	EnemiesAmount = Enemies.Num();
	for (auto Enemy : Enemies)
	{
		AEnemyAIController* enemyController = Cast<AEnemyAIController>(Enemy);
		enemyController->SetEnemyAI(playerCharacter);
		enemyController->OnAiDeadDelegate.AddUObject(this, &ATavernBrawlerGameMode::MakeProgressToWin);
	}

	for (auto tavernFighter : TavernFighters)
	{
		ATavernBrawlerCharacter* tavernCharacter = Cast<ATavernBrawlerCharacter>(tavernFighter);
		tavernCharacter->OnFirstDamageTaken.AddUObject(this, &ATavernBrawlerGameMode::BeginFight);
	}
}

void ATavernBrawlerGameMode::MakeProgressToWin()
{
	EnemiesAmount--;
	if (EnemiesAmount <= 0)
	{
		EndLevel(true);
	}
}

void ATavernBrawlerGameMode::SetGameLost()
{
	EndLevel(false);
}

void ATavernBrawlerGameMode::EndLevel(bool gameIsWon)
{
	playerController->GetPawn()->DisableInput(playerController);
	ATavernBrawlerPlayerController* playerBrawlerController = Cast<ATavernBrawlerPlayerController>(playerController);
	playerBrawlerController->DisablePlayerHUD();
	switch (gameIsWon)
	{
		case true:
			playerBrawlerController->ActivateWinMenu();
			break;
		case false:
			playerBrawlerController->ActivateLoseMenu();
			break;
	}

	playerController->bShowMouseCursor = true;
	playerController->SetInputMode(FInputModeUIOnly());
}
