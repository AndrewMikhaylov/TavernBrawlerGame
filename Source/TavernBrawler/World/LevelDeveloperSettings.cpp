// Fill out your copyright notice in the Description page of Project Settings.


#include "World/LevelDeveloperSettings.h"

UObjectPoolLevelData* ULevelDeveloperSettings::GetObjectPoolLevelData() const
{
	return PoolLevelData.LoadSynchronous();
}
