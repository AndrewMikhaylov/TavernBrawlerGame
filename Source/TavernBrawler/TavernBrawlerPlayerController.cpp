// Copyright Epic Games, Inc. All Rights Reserved.


#include "TavernBrawlerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "TavernBrawlerCameraManager.h"

ATavernBrawlerPlayerController::ATavernBrawlerPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ATavernBrawlerCameraManager::StaticClass();
}

void ATavernBrawlerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}

void ATavernBrawlerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
	
}
