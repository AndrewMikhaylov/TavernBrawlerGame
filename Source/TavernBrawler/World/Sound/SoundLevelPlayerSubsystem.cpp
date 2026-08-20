// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Sound/SoundLevelPlayerSubsystem.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/LevelDeveloperSettings.h"

void USoundLevelPlayerSubsystem::PlayWorldSound(TSoftObjectPtr<USoundBase> soundToPlay)
{
	BackgroundMusic = UGameplayStatics::SpawnSound2D(GetWorld(), soundToPlay.LoadSynchronous());
	BackgroundMusic->Activate();
}

void USoundLevelPlayerSubsystem::StopWorldSound()
{
	BackgroundMusic->FadeOut(1.0f, 0.0f);
}

void USoundLevelPlayerSubsystem::PlaySoundEffect(TSoftObjectPtr<USoundBase> soundToPlay, FVector location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), soundToPlay.LoadSynchronous(), location);
}


void USoundLevelPlayerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	const ULevelDeveloperSettings* settings = GetDefault<ULevelDeveloperSettings>();
	TSoftObjectPtr<USoundBase> soundToPlay = settings->GetBackGroundMusic(UGameplayStatics::GetCurrentLevelName(GetWorld()));
	PlayWorldSound(soundToPlay);
}


