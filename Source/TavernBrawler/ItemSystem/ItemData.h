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
	float UnbrokenThrowDamage;

	UPROPERTY(EditDefaultsOnly)
	float UnbrokenHitDamage;

	UPROPERTY(EditDefaultsOnly)
	float BrokenThrowDamage;

	UPROPERTY(EditDefaultsOnly)
	float BrokenHitDamage;

	UPROPERTY(EditDefaultsOnly)
	float ThrowStrength = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* UnbrokenVisualMesh;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* BrokenVisualMesh;
};
