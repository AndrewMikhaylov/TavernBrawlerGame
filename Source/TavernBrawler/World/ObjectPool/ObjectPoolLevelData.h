// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableObject.h"
#include "Engine/DataAsset.h"
#include "ObjectPoolLevelData.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UObjectPoolLevelData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APoolableObject>> PoolableObjects;

	UPROPERTY(EditAnywhere)
	int PoolSize;
};
