// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HealthData.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UHealthData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	int Health;
};
