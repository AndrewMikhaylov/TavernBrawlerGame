// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMusicDataAsset.h"

TSoftObjectPtr<USoundBase> ULevelMusicDataAsset::GetSoundByLevelNumber(FString levelName)
{
	return LevelMusicMap[levelName];
}
