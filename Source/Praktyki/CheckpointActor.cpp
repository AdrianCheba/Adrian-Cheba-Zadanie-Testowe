// Copyright 2023 Teyon. All Rights Reserved.


#include "CheckpointActor.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

