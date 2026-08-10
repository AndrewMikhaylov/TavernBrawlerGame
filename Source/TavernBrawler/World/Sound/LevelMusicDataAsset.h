// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelMusicDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API ULevelMusicDataAsset : public UDataAsset
{
	GENERATED_BODY()


	public:
	TSoftObjectPtr<USoundBase> GetSoundByLevelNumber(FString levelName);
private:
	UPROPERTY(EditAnywhere)
	TMap<FString, TSoftObjectPtr<USoundBase>> LevelMusicMap;
};
