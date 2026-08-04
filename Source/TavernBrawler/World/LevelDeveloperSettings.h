// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ObjectPool/ObjectPoolLevelData.h"
#include "LevelDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class TAVERNBRAWLER_API ULevelDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UObjectPoolLevelData* GetObjectPoolLevelData() const;

protected:
	UPROPERTY(Config, EditAnywhere, Category="Object Pool")
	TSoftObjectPtr<UObjectPoolLevelData> PoolLevelData;
};
