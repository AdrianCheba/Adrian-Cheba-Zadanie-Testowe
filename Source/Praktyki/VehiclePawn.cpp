// Copyright 2023 Teyon. All Rights Reserved.


#include "VehiclePawn.h"
#include "ChaosVehicleMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h" 
#include "InputActionValue.h"

AVehiclePawn::AVehiclePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600;
	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(-10, 0, 0));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void AVehiclePawn::Tick(float DeltaTime)
{
}

void AVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	input->BindAction(HandBrakeAction, ETriggerEvent::Triggered, this, &AVehiclePawn::OnHandBrakePressed);
	input->BindAction(HandBrakeAction, ETriggerEvent::Completed, this, &AVehiclePawn::OnHandBrakeReleased);
	input->BindAction(ThrottleAction, ETriggerEvent::Started, this, &AVehiclePawn::MoveForward);
	input->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AVehiclePawn::OnThrottleReleased);
	input->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AVehiclePawn::MoveBackward);
	input->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &AVehiclePawn::LookAround);
	input->BindAction(LookUpDownAction, ETriggerEvent::Triggered, this, &AVehiclePawn::LookUpDown);
	input->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AVehiclePawn::Steering);
	input->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AVehiclePawn::SteeringReleased);
}



void AVehiclePawn::MoveForward(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value.Get<float>());
}

void AVehiclePawn::MoveBackward(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(Value.Get<float>() / 1.5);
}

void AVehiclePawn::LookAround(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void AVehiclePawn::LookUpDown(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>() / -10);
}

void AVehiclePawn::Steering(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value.Get<float>());
}

void AVehiclePawn::SteeringReleased()
{
	GetVehicleMovementComponent()->SetSteeringInput(0);
}

void AVehiclePawn::OnHandBrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AVehiclePawn::OnHandBrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AVehiclePawn::OnThrottleReleased()
{
	GetVehicleMovementComponent()->SetThrottleInput(0);
}
