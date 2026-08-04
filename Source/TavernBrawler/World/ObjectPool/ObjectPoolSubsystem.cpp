// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ObjectPool/ObjectPoolSubsystem.h"

#include "ItemSystem/InteractableItem.h"
#include "World/LevelDeveloperSettings.h"

void UObjectPoolSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	SetPoolData();
	
	for (auto poolableObjectSubclass : PoolData->PoolableObjects)
	{
		FString poolName = poolableObjectSubclass->GetDefaultObject<APoolableObject>()->Name;
		TArray<APoolableObject*> poolableObjectsOfType;
		for (int i = 0; i < PoolData->PoolSize; ++i)
		{
			APoolableObject* PoolableObject = CreatePoolableObject(poolableObjectSubclass, i);
			if (PoolableObject)
			{
				PoolableObject->Activate(false);
				PoolableObject->OnObjectDestroyed.AddUObject(this, &UObjectPoolSubsystem::DeactivatePoolableObject);
				poolableObjectsOfType.Add(PoolableObject);
			}
		}
		PoolMap.Add(poolName, poolableObjectsOfType);
	}
}

AInteractableItem* UObjectPoolSubsystem::ActivatePoolableObject(FString name)
{
	TArray<APoolableObject*>* poolableObjectsOfType = PoolMap.Find(name);
	if (poolableObjectsOfType != nullptr)
	{
		for (APoolableObject* poolableObject : *poolableObjectsOfType)
		{
			if (!poolableObject->CheckIsActive())
			{
				poolableObject->Activate(true);
				return Cast<AInteractableItem>(poolableObject);
			}
		}
		APoolableObject* createdPoolableObject =CreatePoolableObject((*poolableObjectsOfType)[0]->GetClass(), poolableObjectsOfType->Num());
		if (createdPoolableObject)
		{
			createdPoolableObject->Activate(true);
			poolableObjectsOfType->Add(createdPoolableObject);
			return Cast<AInteractableItem>(createdPoolableObject);
		}
	}
	return nullptr;
}

void UObjectPoolSubsystem::DeactivatePoolableObject(FString name, int index)
{
	TArray<APoolableObject*>* poolableObjectsOfType = PoolMap.Find(name);
	if (poolableObjectsOfType != nullptr)
	{
		for (APoolableObject* poolableObject : *poolableObjectsOfType)
		{
			if(poolableObject->GetIndex() == index)
			{
				poolableObject->Activate(false);
			}
		}
	}
}

bool UObjectPoolSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (UWorld* world = Cast<UWorld>(Outer))
	{
		FString worldName = world->GetName();
		if (worldName.Contains("MainMenuLevel"))
		{
			return false;
		}
	}
	return Super::ShouldCreateSubsystem(Outer);
}

APoolableObject* UObjectPoolSubsystem::CreatePoolableObject(TSubclassOf<APoolableObject> poolableObjectSubclass, int index)
{
	AActor* poolableObjectActor = GetWorld()->SpawnActor(poolableObjectSubclass);
	APoolableObject* PoolableObject = Cast<APoolableObject>(poolableObjectActor);
	if (PoolableObject != nullptr)
	{
		PoolableObject->SetIndex(index);
		PoolableObject->Activate(false);
		return PoolableObject;
	}
	return nullptr;
}

void UObjectPoolSubsystem::SetPoolData()
{
	const ULevelDeveloperSettings* settings = GetDefault<ULevelDeveloperSettings>();
	PoolData = settings->GetObjectPoolLevelData();
}
