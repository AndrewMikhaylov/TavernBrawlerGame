// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EAttackState.h"
#include "PlayerAttacker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAVERNBRAWLER_API UPlayerAttacker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerAttacker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	EAttackState AttackState;
	float AttackAlpha;
	AActor* RightHandActor;
	FVector attackEndPosition;
	FVector attackStartPosition;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	void DoHitMovement(AActor* rightHand);
	
	DECLARE_MULTICAST_DELEGATE(OnAttackEnded)
	OnAttackEnded AttackEnded;
};
