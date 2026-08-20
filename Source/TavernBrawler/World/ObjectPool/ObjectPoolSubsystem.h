// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPoolLevelData.h"
#include "ItemSystem/InteractableItem.h"
#include "World/ObjectPool/PoolableObject.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UObjectPoolLevelData* PoolData;
	TMap<FString, TArray<APoolableObject*>> PoolMap;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	APoolableObject* CreatePoolableObject(TSubclassOf<APoolableObject> poolableObjectSubclass, int index);

	void SetPoolData();
	void AddExistingObjectsToPool();
public:
	AInteractableItem* ActivatePoolableObject(FString name);
	void DeactivatePoolableObject(FString name, int index);
	
};
