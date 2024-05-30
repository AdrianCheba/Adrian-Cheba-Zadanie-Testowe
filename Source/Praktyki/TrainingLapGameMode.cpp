// Copyright 2023 Teyon. All Rights Reserved.


#include "TrainingLapGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "CheckpointActor.h"
#include "TimerManager.h"

void ATrainingLapGameMode::FinishedLap(APawn* Car)
{
	Super::FinishedLap(Car);

	for (ACheckpointActor* CheckPoint : TActorRange<ACheckpointActor>(GetWorld())) 
	{
		if (!CheckPoint->IsDeactivated)
			return;
	}

	EndGame(true);
	Car->DetachFromControllerPendingDestroy();
}

void ATrainingLapGameMode::DestroyedCar(APawn* Car)
{
	Super::DestroyedCar(Car);

	APlayerController* PlayerController = Cast<APlayerController>(Car->GetController());
	if (PlayerController) 
	{
		EndGame(false);
		Car->DetachFromControllerPendingDestroy();
	}
}

void ATrainingLapGameMode::LapManager(APawn* Car, float CurrentLapTime)
{
	CurrentLapTime = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentLapTime);
}

void ATrainingLapGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld())) 
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

void ATrainingLapGameMode::TimeUp()
{
	EndGame(false);
}
