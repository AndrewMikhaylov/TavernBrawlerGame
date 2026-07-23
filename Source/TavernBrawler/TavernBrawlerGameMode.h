// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TavernBrawlerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "UI/HUDEndGameWidget.h"
#include "TavernBrawlerGameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class ATavernBrawlerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATavernBrawlerGameMode();

	virtual void Tick(float DeltaSeconds) override;

	void BeginFight();
protected:
	virtual void BeginPlay() override;
	TArray<AActor*> Enemies;
	TArray<AActor*> TavernFighters;
	ATavernBrawlerCharacter* playerCharacter;
	APlayerController* playerController;
	bool bFightStarted = false;
	int EnemiesAmount;
	
	void MakeProgressToWin();
	void SetGameLost();
	void EndLevel(bool gameIsWon);

};



