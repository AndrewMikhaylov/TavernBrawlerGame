// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
}
