// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health/HealthData.h"
#include "ActorHealthSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAVERNBRAWLER_API UActorHealthSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorHealthSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

   

	int GetActorHealth();

	int CurrentHealth;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetHealth();
	void TakeDamage(int damage);

	DECLARE_MULTICAST_DELEGATE(FActorDied);
	FActorDied ActorDied;
	
	UPROPERTY(EditAnywhere)
    	UHealthData* HealthData;
	bool IsCharacterAlive() const;
};
