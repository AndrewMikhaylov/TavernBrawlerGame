// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackSystem/PlayerAttacker.h"

// Sets default values for this component's properties
UPlayerAttacker::UPlayerAttacker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerAttacker::BeginPlay()
{
	Super::BeginPlay();

	AttackState=EAttackState::Idle;	
}


// Called every frame
void UPlayerAttacker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (AttackState)
	{
	case EAttackState::Idle:
		break;
	case EAttackState::Attacking:
		AttackAlpha+=DeltaTime*8.f;
		RightHandActor->GetRootComponent()->SetRelativeLocation(FMath::Lerp(attackStartPosition, attackEndPosition, AttackAlpha),true);
		
		if (AttackAlpha>=1.f)
		{
			AttackAlpha=0;
			AttackState = EAttackState::Returning;
		}
		break;

	case EAttackState::Returning:
		AttackAlpha+=DeltaTime*4.f;
		RightHandActor->GetRootComponent()->SetRelativeLocation(FMath::Lerp(attackEndPosition, attackStartPosition, AttackAlpha),true);
		if (AttackAlpha>=1.f)
		{
			AttackState = EAttackState::Idle;
			RightHandActor->GetRootComponent()->SetRelativeLocation(attackStartPosition);
			AttackEnded.Broadcast();
		}
		break;
	}
}

void UPlayerAttacker::DoHitMovement(AActor* rightHand)
{
	// if weapon in hand rotate weapon around body if not spawn fist and move it forward
	if (rightHand)
	{
		RightHandActor = rightHand;
	}
	attackStartPosition =
			RightHandActor->GetRootComponent()->GetRelativeLocation();

	FVector Forward = -FVector::LeftVector;

	FVector Right = FVector::CrossProduct(FVector::UpVector, Forward);
	Right.Normalize();

	FVector SlashOffset =
		Forward*100.f - Right*50.f;

	attackEndPosition =
		attackStartPosition + SlashOffset;

	AttackAlpha = 0.f;
	AttackState = EAttackState::Attacking;
}




