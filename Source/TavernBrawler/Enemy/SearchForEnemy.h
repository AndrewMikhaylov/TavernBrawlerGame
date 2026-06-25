// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TavernBrawlerCharacter.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SearchForEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API USearchForEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USearchForEnemy();
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CurrentEnemy;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SearchRadius;
		

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
