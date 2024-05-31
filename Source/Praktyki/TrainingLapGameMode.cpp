// Copyright 2023 Teyon. All Rights Reserved.


#include "TrainingLapGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "CheckpointActor.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"


void ATrainingLapGameMode::FinishedLap(APawn* Car)
{
	Super::FinishedLap(Car);

	for (ACheckpointActor* CheckPoint : TActorRange<ACheckpointActor>(GetWorld())) 
	{
		if (!CheckPoint->IsDeactivated)
			return;
	}

	if (CurrentLap != NumberOfLaps)
	{
		for (ACheckpointActor* CheckPoint : TActorRange<ACheckpointActor>(GetWorld()))
			CheckPoint->ActivateCheckpoint();

		LastLapTime = CurrentLapTime - LastLapTime;

		if(CurrentLap == 1)
			BestLapTime = LastLapTime;
		else 
			if(BestLapTime > LastLapTime)
				BestLapTime = LastLapTime;

		CurrentLap++;
	}
	else 
	{
		LastLapTime = CurrentLapTime - LastLapTime;

		if (BestLapTime > LastLapTime || CurrentLap == 1)
			BestLapTime = LastLapTime;

		EndGame(true);
		MuteAll(Car);
	}

	
}

void ATrainingLapGameMode::DestroyedCar(APawn* Car)
{
	Super::DestroyedCar(Car);

	APlayerController* PlayerController = Cast<APlayerController>(Car->GetController());
	if (PlayerController) 
	{
		EndGame(false);
		MuteAll(Car);
	}
}

void ATrainingLapGameMode::LapManager(APawn* Car, float Laps, float LapTime)
{
	NumberOfLaps = Laps;
	CurrentLapTime = LapTime;
}

void ATrainingLapGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld())) 
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
		GetWorld()->GetWorldSettings()->SetTimeDilation(0.0f);
	}
}

void ATrainingLapGameMode::MuteAll(APawn* Car)
{
	TArray<UAudioComponent*> AudioComponents;
	Car->GetComponents<UAudioComponent>(AudioComponents);
	for (UAudioComponent* AudioComponent : AudioComponents)
	{
		if (AudioComponent)
		{
			AudioComponent->SetVolumeMultiplier(0.0f);
		}
	}
}

void ATrainingLapGameMode::TimeUp(APawn* Car)
{
	EndGame(false);
	MuteAll(Car);
}
