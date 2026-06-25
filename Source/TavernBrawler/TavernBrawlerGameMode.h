// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
protected:
	virtual void BeginPlay() override;
};



