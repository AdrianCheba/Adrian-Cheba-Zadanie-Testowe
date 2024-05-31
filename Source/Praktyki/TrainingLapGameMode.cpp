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

	if (CurrentLap == NumberOfLaps)
		EndGame(true);
	else 
	{
		CurrentLap++;
		for (ACheckpointActor* CheckPoint : TActorRange<ACheckpointActor>(GetWorld()))
		{
			if (CheckPoint->IsDeactivated)
				CheckPoint->ActivateCheckpoint();
		}
	}

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

void ATrainingLapGameMode::DestroyedCar(APawn* Car)
{
	Super::DestroyedCar(Car);

	APlayerController* PlayerController = Cast<APlayerController>(Car->GetController());
	if (PlayerController) 
	{
		EndGame(false);
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
}

void ATrainingLapGameMode::LapManager(APawn* Car, float Laps)
{
	NumberOfLaps = Laps;
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

void ATrainingLapGameMode::TimeUp(APawn* Car)
{
	EndGame(false);
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
