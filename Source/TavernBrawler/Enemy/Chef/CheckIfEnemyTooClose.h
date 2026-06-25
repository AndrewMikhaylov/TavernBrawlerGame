// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CheckIfEnemyTooClose.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UCheckIfEnemyTooClose : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCheckIfEnemyTooClose();
	
protected:
	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector CurrentEnemy;
	
	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector MaxDistance;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
