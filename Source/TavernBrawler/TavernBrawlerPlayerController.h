// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/HUDWidget.h"
#include "TavernBrawlerPlayerController.generated.h"

class UInputMappingContext;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract)
class TAVERNBRAWLER_API ATavernBrawlerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	ATavernBrawlerPlayerController();
	UPROPERTY(VisibleAnywhere)
	UHUDWidget* HUDWidget;
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;
	
};
