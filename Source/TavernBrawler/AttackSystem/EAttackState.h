// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAttackState.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EAttackState : uint8
{
 Idle    UMETA(DisplayName = "Idle"),
 Attacking UMETA(DisplayName = "Attacking"),
 Returning UMETA(DisplayName = "Returning"),
};
