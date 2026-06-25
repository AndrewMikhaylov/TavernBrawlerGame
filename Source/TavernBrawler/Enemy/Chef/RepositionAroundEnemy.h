// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RepositionAroundEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API URepositionAroundEnemy : public UBTTaskNode
{
	GENERATED_BODY()

	public:
	URepositionAroundEnemy();

	UPROPERTY(Category = Decorator , EditAnywhere)
	FBlackboardKeySelector LocationAroundEnemy;
	UPROPERTY(Category = Decorator , EditAnywhere)
	float RepositionRadius;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
