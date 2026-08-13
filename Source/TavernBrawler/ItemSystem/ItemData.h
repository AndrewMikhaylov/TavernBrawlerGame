// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:
	UPROPERTY(EditDefaultsOnly)
	int Durability;

	UPROPERTY(EditDefaultsOnly)
	float ThrowDamage;

	UPROPERTY(EditDefaultsOnly)
	float HitDamage;
	
	UPROPERTY(EditDefaultsOnly)
	float ThrowStrength = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* VisualMesh;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> BrokenActors;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USoundBase> soundToPlay;
};
