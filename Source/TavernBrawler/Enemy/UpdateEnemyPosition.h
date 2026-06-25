// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UpdateEnemyPosition.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UUpdateEnemyPosition : public UBTService
{
	GENERATED_BODY()
public:

	UPROPERTY(Category = Decorator, EditAnywhere)
	FBlackboardKeySelector CurrentEnemyPosition;
	
	UUpdateEnemyPosition();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
