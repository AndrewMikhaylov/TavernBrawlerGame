// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	// create TMAP for interactableobject name : array of objects of this name functions for spawning deleting and creating objects by index
	// in begin play create 20 of every object
	// separate function for fist
};
