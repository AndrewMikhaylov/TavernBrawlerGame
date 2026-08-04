// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableObject.generated.h"

UCLASS()
class TAVERNBRAWLER_API APoolableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolableObject();

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectDestroyed, FString, int);
	FOnObjectDestroyed OnObjectDestroyed;
	
	UPROPERTY(EditAnywhere)
	FString Name;
	
	int GetIndex();
	bool CheckIsActive();
	void SetIndex(int index);
	void Activate(bool isActive);
	
// set active and deactivate
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int Index;
	bool IsActive;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
