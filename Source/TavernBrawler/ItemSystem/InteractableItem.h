// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "ItemSystem/ItemData.h"
#include "InteractableItem.generated.h"

UCLASS()
class TAVERNBRAWLER_API AInteractableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* hurtMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* visualMesh;
	
	UPROPERTY(EditAnywhere)
	UItemData* ItemData;
	
	float CurrentDurability;
	float CurrentDamage;
	float CurrentThrowDamage;
	bool IsThrown=false;
	bool IsAttacking = false;
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

public:

	DECLARE_MULTICAST_DELEGATE(FOnItemBroken)
	FOnItemBroken OnItemBroken;

	void Throw(FVector Direction);

	void BeginHitOnOverlap();

	UFUNCTION()
	void DealThrowDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void PickUp();
	void DeactivateOverlap();
private:
	void InitializeItem();
	void BreakTransformItem();
	void BreakItem();


};
