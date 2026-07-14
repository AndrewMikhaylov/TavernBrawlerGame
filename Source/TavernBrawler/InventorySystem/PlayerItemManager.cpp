// Fill out your copyright notice in the Description page of Project Settings.

#include "InventorySystem/PlayerItemManager.h"

// Sets default values for this component's properties
UPlayerItemManager::UPlayerItemManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}


// Called when the game starts
void UPlayerItemManager::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UPlayerItemManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerItemManager::TakeToThrow(FVector StartPosition, FVector LookingDirection)
{
	if (IsThrowHandEmpty)
	{
		AInteractableItem* itemToThrow = TakeItem(StartPosition, LookingDirection);
		if (itemToThrow)
		{
			IsThrowHandEmpty = false;
			EquipAsThrowWeapon(itemToThrow);
			currentThrowItem = itemToThrow;
		}
	}
}

void UPlayerItemManager::TakeToThrow(AInteractableItem* itemToThrow)
{
	if (IsThrowHandEmpty)
	{
		if (itemToThrow)
		{
			IsThrowHandEmpty = false;
			EquipAsThrowWeapon(itemToThrow);
			currentThrowItem = itemToThrow;
		}
	}
}

void UPlayerItemManager::TakeToFight(FVector StartPosition, FVector LookingDirection)
{
	AInteractableItem* itemToFight = TakeItem(StartPosition, LookingDirection);
	if (itemToFight)
	{
		if (currentFightItem)
		{
			FreeFightingHand(nullptr);
		}
		EquipAsFightWeapon(itemToFight);
		currentFightItem = itemToFight;
		currentFightItem->OnItemBroken.AddUObject(this, &UPlayerItemManager::FreeFightingHand);
		IsFightHandEmpty = false;
	}
	else
	{
		IsFightHandEmpty = true;
	}
}

void UPlayerItemManager::Throw(FVector throwDirection)
{
	if (!IsThrowHandEmpty && currentThrowItem)
	{
		currentThrowItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		currentThrowItem->Throw(throwDirection);
		currentThrowItem = nullptr;
		IsThrowHandEmpty = true;
	}
}

void UPlayerItemManager::BeginHitting()
{
	if (currentFightItem)
	{
		currentFightItem->BeginHitOnOverlap();
	}
}

void UPlayerItemManager::SetupHandSockets(UStaticMeshComponent* leftHand, UStaticMeshComponent* rightHand)
{
	LeftHand = leftHand;
	RightHand = rightHand;
	IsThrowHandEmpty = true;
}

AInteractableItem* UPlayerItemManager::GetCurrentFightItem()
{
	if (currentFightItem)
	{
		return currentFightItem;
	}
	basicWeaponActor = GetWorld()->SpawnActor(BasicWeaponClass);
	AInteractableItem* basicWeapon = Cast<AInteractableItem>(basicWeaponActor);
	EquipAsFightWeapon(basicWeapon);
	currentFightItem = basicWeapon;
	return currentFightItem;
}

void UPlayerItemManager::EndAttack()
{
	currentFightItem->DeactivateOverlap();
	if (IsFightHandEmpty)
	{
		FreeFightingHand(nullptr);
		if (basicWeaponActor)
		{
			GetWorld()->DestroyActor(basicWeaponActor);
			basicWeaponActor=nullptr;	
		}
	}
}

FVector UPlayerItemManager::CalculateEndPosition(FVector StartPosition, FVector LookingDirection)
{
	return StartPosition + TakingDistance * LookingDirection;;
}

AInteractableItem* UPlayerItemManager::TakeItem(FVector StartPosition, FVector LookingDirection)
{
	FVector EndPosition = CalculateEndPosition(StartPosition, LookingDirection);
	FHitResult hitResult;
	FCollisionShape interactSphere = FCollisionShape::MakeSphere(SphereRadius);
	bool isHitItem = GetWorld()->SweepSingleByChannel(hitResult, StartPosition, EndPosition, FQuat::Identity, ECC_GameTraceChannel2, interactSphere);
	if (isHitItem)
	{
		AInteractableItem* item = Cast<AInteractableItem>(hitResult.GetActor());

		if (item)
		{
			return item;
		}
	}
	return nullptr;
}

void UPlayerItemManager::EquipAsThrowWeapon(AInteractableItem* throwableItem)
{

	throwableItem->PickUp(GetOwner());
	throwableItem->AttachToComponent(LeftHand, FAttachmentTransformRules::SnapToTargetIncludingScale, "hand_l_socket");
}

void UPlayerItemManager::EquipAsFightWeapon(AInteractableItem* meleeItem)
{

	meleeItem->PickUp(GetOwner());
	meleeItem->AttachToComponent(RightHand, FAttachmentTransformRules::SnapToTargetIncludingScale, "hand_r_socket");
}

void UPlayerItemManager::FreeFightingHand(AInteractableItem* newItem)
{
	if (newItem)
	{
		currentFightItem = newItem;
		EquipAsFightWeapon(newItem);
	}
	else
	{
		if (currentFightItem)
		{
			currentFightItem->OnItemBroken.RemoveAll(this);
			currentFightItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			IsFightHandEmpty = true;
			currentFightItem = nullptr;	
		}	
	}
}

