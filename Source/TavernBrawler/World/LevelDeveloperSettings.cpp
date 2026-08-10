// Fill out your copyright notice in the Description page of Project Settings.


#include "World/LevelDeveloperSettings.h"

UObjectPoolLevelData* ULevelDeveloperSettings::GetObjectPoolLevelData() const
{
	return PoolLevelData.LoadSynchronous();
}

TSoftObjectPtr<USoundBase> ULevelDeveloperSettings::GetBackGroundMusic(FString levelName) const
{
	ULevelMusicDataAsset* musicData = MusicDataAsset.LoadSynchronous();
	if (musicData)
	{
		return musicData->GetSoundByLevelNumber(levelName);
	}
	return nullptr;
}
