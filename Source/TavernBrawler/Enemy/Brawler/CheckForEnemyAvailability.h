// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CheckForEnemyAvailability.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UCheckForEnemyAvailability : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCheckForEnemyAvailability();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector CurrentEnemy;
};
