// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CheckIfThisEnemyIsAlive.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UCheckIfThisEnemyIsAlive : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCheckIfThisEnemyIsAlive();
	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector IsAlive;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
