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

void UPlayerItemManager::TakeToFight(FVector StartPosition, FVector LookingDirection)
{
	AInteractableItem* itemToFight = TakeItem(StartPosition, LookingDirection);
	FreeFightingHand();
	if (itemToFight)
	{
		EquipAsFightWeapon(itemToFight);
		currentFightItem = itemToFight;
		currentFightItem->OnItemBroken.AddUObject(this, &UPlayerItemManager::FreeFightingHand);
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

void UPlayerItemManager::Hit()
{
	currentFightItem->DealHitDamage();
}

void UPlayerItemManager::SetupHandSockets(UStaticMeshComponent* leftHand, UStaticMeshComponent* rightHand)
{
	LeftHand = leftHand;
	RightHand = rightHand;
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

	throwableItem->PickUp();
	throwableItem->AttachToComponent(LeftHand, FAttachmentTransformRules::SnapToTargetIncludingScale, "hand_l_socket");
}

void UPlayerItemManager::EquipAsFightWeapon(AInteractableItem* meleeItem)
{

	meleeItem->PickUp();
	meleeItem->AttachToComponent(RightHand, FAttachmentTransformRules::SnapToTargetIncludingScale, "hand_r_socket");
}

void UPlayerItemManager::FreeFightingHand()
{
	currentFightItem->OnItemBroken.RemoveAll(this);
	currentFightItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
	currentFightItem = nullptr;

}

