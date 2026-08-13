// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "ItemSystem/ItemData.h"
#include "World/ObjectPool/PoolableObject.h"
#include "InteractableItem.generated.h"

UCLASS()
class TAVERNBRAWLER_API AInteractableItem : public APoolableObject
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
	UBoxComponent* hurtMesh;
	
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

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemBroken, AInteractableItem*);
	FOnItemBroken OnItemBroken;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemSoundPlay, TSoftObjectPtr<USoundBase>, FVector);
	FOnItemSoundPlay OnItemSoundPlay;
		
	void Throw(FVector Direction);

	void BeginHitOnOverlap();

	UFUNCTION()
	void DealThrowDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void PickUp(AActor* ItemOwner);
	void DeactivateOverlap();
	void Activate(bool isActive) override;
private:
	void InitializeItem();
	void BreakTransformItem();
	void BreakItem();
	void PlaySound();
	
	AActor* ThisItemOwner;
	FCollisionResponseContainer CollisionParameters;
	AInteractableItem* nextItem;
	TArray<AActor*> ActorsHit;


};
