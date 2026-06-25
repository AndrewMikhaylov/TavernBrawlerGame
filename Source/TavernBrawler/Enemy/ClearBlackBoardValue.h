// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ClearBlackBoardValue.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UClearBlackBoardValue : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UClearBlackBoardValue();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
			
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector KeyToClear;
};