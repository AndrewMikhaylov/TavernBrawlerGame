// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TavernBrawlerCharacter.h"
#include "ItemSystem/InteractableItem.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	void SetEnemyAI(ATavernBrawlerCharacter* playerCharacter);
	void SetIsDead();
	ATavernBrawlerCharacter* ThisCharacter;
	ATavernBrawlerCharacter* Player;
	ATavernBrawlerCharacter* CurrentEnemy;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking;

	UPROPERTY(BlueprintReadWrite)
	bool bIsReadyToFight = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead = false;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AInteractableItem> InteractableItem;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	DECLARE_MULTICAST_DELEGATE(OnAiDead)
	OnAiDead OnAiDeadDelegate;
	
	void Attack();
	void SetReadyToFight();
};
