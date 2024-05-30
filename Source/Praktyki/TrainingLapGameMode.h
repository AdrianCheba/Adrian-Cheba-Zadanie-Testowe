// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PraktykiGameModeBase.h"
#include "TrainingLapGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API ATrainingLapGameMode : public APraktykiGameModeBase
{
	GENERATED_BODY()

public:
	virtual void FinishedLap(APawn* Car) override;
	virtual void DestroyedCar(APawn* Car) override;
	virtual void LapManager(APawn* Car, float CurrentLapTime) override;
	virtual void TimeUp() override;

private:
	void EndGame(bool bIsPlayerWinner);
	FTimerHandle MaxLapTimeHandle;
	
};
