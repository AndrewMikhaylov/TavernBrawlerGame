// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SoundLevelPlayerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TAVERNBRAWLER_API USoundLevelPlayerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	public:
	void PlayWorldSound(TSoftObjectPtr<USoundBase> soundToPlay);
	void StopWorldSound();
	void PlaySoundEffect(TSoftObjectPtr<USoundBase> soundToPlay, FVector location);
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	UPROPERTY()
	UAudioComponent* BackgroundMusic;
};
