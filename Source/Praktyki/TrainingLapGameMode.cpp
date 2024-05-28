// Copyright 2023 Teyon. All Rights Reserved.


#include "TrainingLapGameMode.h"

void ATrainingLapGameMode::DestroyedCar(APawn* Car)
{
	Super::DestroyedCar(Car);
		
	APlayerController* PlayerController = Cast<APlayerController>(Car->GetController());
	if (PlayerController)
		PlayerController->GameHasEnded(nullptr, false);
}
