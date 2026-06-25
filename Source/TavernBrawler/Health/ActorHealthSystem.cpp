// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/ActorHealthSystem.h"

// Sets default values for this component's properties
UActorHealthSystem::UActorHealthSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorHealthSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorHealthSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UActorHealthSystem::GetActorHealth()
{
	return HealthData->Health;
}

void UActorHealthSystem::SetHealth()
{
	CurrentHealth = GetActorHealth();
}

void UActorHealthSystem::TakeDamage(int damage)
{
	CurrentHealth -= damage;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		ActorDied.Broadcast();
	}
}

bool UActorHealthSystem::IsCharacterAlive() const
{
	if (CurrentHealth>0)
	{
		return true;
	}
	return false;
}



