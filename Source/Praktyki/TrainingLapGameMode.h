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
	virtual void LapManager(APawn* Car, float Laps, float LapTime) override;
	virtual void TimeUp(APawn* Car) override;

	float MaxLapTime;
	float NumberOfLaps;
	float CurrentLap = 1;
	float CurrentLapTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastLapTime = 0;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BestLapTime = 0;

private:
	void EndGame(bool bIsPlayerWinner);
	void MuteAll(APawn* Car);
};
