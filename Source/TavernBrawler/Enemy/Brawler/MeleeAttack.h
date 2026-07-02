// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UMeleeAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector AttackRange;

	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector CurrentEnemy;

	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector AttackDamage;
};
