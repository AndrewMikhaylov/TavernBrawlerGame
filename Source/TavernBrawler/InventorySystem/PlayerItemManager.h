// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemSystem/InteractableItem.h"
#include "PlayerItemManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAVERNBRAWLER_API UPlayerItemManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerItemManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void TakeToThrow(FVector StartPosition, FVector LookingDirection);

	void TakeToFight(FVector StartPosition, FVector LookingDirection);

	void Throw(FVector throwDirection);

	void Hit();

	void SetupHandSockets(UStaticMeshComponent* leftHand, UStaticMeshComponent* rightHand);

protected:
	UPROPERTY(EditAnywhere, Category="Take")
	float TakingDistance;

	UPROPERTY(EditAnywhere, Category = "Throw")
	float ThrowForce;

	UPROPERTY(EditAnywhere, Category="Interact")
	float SphereRadius;

	UStaticMeshComponent* LeftHand; 
	UStaticMeshComponent* RightHand;

	AInteractableItem* currentThrowItem;
	AInteractableItem* currentFightItem;


private:
	bool IsThrowHandEmpty;

	FVector CalculateEndPosition(FVector StartPosition, FVector LookingDirection);
	AInteractableItem* TakeItem(FVector StartPosition, FVector LookingDirection);
	void EquipAsThrowWeapon(AInteractableItem* throwableItem);
	void EquipAsFightWeapon(AInteractableItem* meleeItem);
	void FreeFightingHand();

};
