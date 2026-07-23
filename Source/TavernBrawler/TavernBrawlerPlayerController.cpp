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

	bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
	
}

void ATavernBrawlerPlayerController::ActivateWinMenu()
{
	HUDWidgetEndScreen = CreateWidget<UHUDEndGameWidget>(this, HUDWidgetWin);
	if (HUDWidgetEndScreen)
	{
		HUDWidgetEndScreen->AddToViewport();
	}
}

void ATavernBrawlerPlayerController::ActivateLoseMenu()
{
	HUDWidgetEndScreen = CreateWidget<UHUDEndGameWidget>(this, HUDWidgetLose);
	if (HUDWidgetEndScreen)
	{
		HUDWidgetEndScreen->AddToViewport();
	}
}

void ATavernBrawlerPlayerController::DisablePlayerHUD()
{
	HUDWidget->SetVisibility(ESlateVisibility::Collapsed);
}


