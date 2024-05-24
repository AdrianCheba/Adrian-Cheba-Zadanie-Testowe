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
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AVehiclePawn::AVehiclePawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600;
	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(-10, 0, 0));
	SpringArm->bUsePawnControlRotation = true;

	SpringArm2 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm2"));
	SpringArm2->SetupAttachment(GetMesh());
	SpringArm2->TargetArmLength = 700;
	SpringArm2->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm2->SetRelativeRotation(FRotator(-10, 0, 0));
	SpringArm2->bUsePawnControlRotation = true;

	SpringArm3 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm3"));
	SpringArm3->SetupAttachment(RootComponent);
	SpringArm3->TargetArmLength = 0;
	SpringArm3->SetRelativeLocation(FVector(0, 0, 0));
	SpringArm3->SetRelativeRotation(FRotator(0, 0, 0));
	SpringArm3->bUsePawnControlRotation = false;
	
	Camera1 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	Camera1->SetupAttachment(SpringArm);

	Camera2 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera2"));
	Camera2->SetupAttachment(SpringArm2);

	Camera3 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera3"));
	Camera3->SetupAttachment(GetMesh(), FName("CarAttachedSpectatorWingCamera"));	
	
	Camera4 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera4"));
	Camera4->SetupAttachment(SpringArm3);

	EngineSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Engine Sound"));
	EngineSound->SetupAttachment(GetMesh());

	NS_ExhaustLeft = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Exhaust Left VFX"));
	NS_ExhaustLeft->SetupAttachment(GetMesh(), FName("VfxMainExhaust"));

	NS_ExhaustRight = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Exhaust Right VFX"));
	NS_ExhaustRight->SetupAttachment(GetMesh(), FName("VfxSecondExhaust"));

	SteeringWheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheelMesh->SetupAttachment(GetMesh(), FName(TEXT("SteeringWheel")));

	RearLeftLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RearLeftLight"));
	RearLeftLight->SetupAttachment(GetMesh(), FName(TEXT("RearLeftLight")));
	RearLeftLight->LightColor = FColor::Red;
	
	RearRightLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RearRightLight"));
	RearRightLight->SetupAttachment(GetMesh(), FName(TEXT("RearRightLight")));
	RearRightLight->LightColor = FColor::Red;
	
	RearCenterLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RearCenterLight"));
	RearCenterLight->SetupAttachment(GetMesh(), FName(TEXT("RearCenterLight")));
	RearCenterLight->LightColor = FColor::Red;
}

void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UChaosWheeledVehicleMovementComponent* vehicleComponent = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());

	if (!vehicleComponent)
		return;

	float rpm = vehicleComponent->GetEngineRotationSpeed();

	EngineSound->SetFloatParameter(FName("RPM"), rpm);

	if (rpm > 1500 && rpm < 4500)
		IncreasedSmokeExhaust();
	else
		DecreasedSmokeExhaust();

	SteeringInput = vehicleComponent->GetSteeringInput();
	UpdateSteeringWheelRotation(SteeringInput);
}

void AVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	TurnRearLights(false);
	ActiveCameraIndex = 0;
}

void AVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto PlayerController = Cast<APlayerController>(Controller))
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	input->BindAction(HandBrakeAction, ETriggerEvent::Triggered, this, &AVehiclePawn::OnHandBrakePressed);
	input->BindAction(HandBrakeAction, ETriggerEvent::Completed, this, &AVehiclePawn::OnHandBrakeReleased);
	input->BindAction(ThrottleAction, ETriggerEvent::Started, this, &AVehiclePawn::MoveForward);
	input->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AVehiclePawn::OnThrottleReleased);
	input->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AVehiclePawn::OnBrakePressed);
	input->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AVehiclePawn::OnBrakeReleased);
	input->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &AVehiclePawn::LookAround);
	input->BindAction(LookUpDownAction, ETriggerEvent::Triggered, this, &AVehiclePawn::LookUpDown);
	input->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AVehiclePawn::Steering);
	input->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AVehiclePawn::SteeringReleased);
	input->BindAction(SwitchCameraAction, ETriggerEvent::Triggered, this, &AVehiclePawn::SwitchCamera);
	input->BindAction(InteriorCameraLookAction, ETriggerEvent::Triggered, this, &AVehiclePawn::InteriorCameraLook);
	input->BindAction(InteriorCameraLookAction, ETriggerEvent::Completed, this, &AVehiclePawn::InteriorCameraLookReleased);
}



void AVehiclePawn::MoveForward(const FInputActionValue& value)
{
	GetVehicleMovementComponent()->SetThrottleInput(value.Get<float>());
}

void AVehiclePawn::OnBrakePressed(const FInputActionValue& value)
{
	GetVehicleMovementComponent()->SetBrakeInput(value.Get<float>() / 1.5);
	TurnRearLights(true);
}

void AVehiclePawn::OnBrakeReleased(const FInputActionValue& value)
{
	GetVehicleMovementComponent()->SetBrakeInput(0);
	TurnRearLights(false);
}

void AVehiclePawn::LookAround(const FInputActionValue& value)
{
	AddControllerYawInput(value.Get<float>());
}

void AVehiclePawn::LookUpDown(const FInputActionValue& value)
{
	AddControllerPitchInput(value.Get<float>() / -7);
}

void AVehiclePawn::InteriorCameraLook()
{
	SpringArm3->bUsePawnControlRotation = true;
}

void AVehiclePawn::InteriorCameraLookReleased()
{
	SpringArm3->bUsePawnControlRotation = false;
}

void AVehiclePawn::Steering(const FInputActionValue& value)
{
	GetVehicleMovementComponent()->SetSteeringInput(value.Get<float>());
}

void AVehiclePawn::SteeringReleased()
{
	GetVehicleMovementComponent()->SetSteeringInput(0);
}

void AVehiclePawn::OnHandBrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
	TurnRearLights(true);
}

void AVehiclePawn::OnHandBrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	TurnRearLights(false);
}

void AVehiclePawn::OnThrottleReleased()
{
	GetVehicleMovementComponent()->SetThrottleInput(0);

}

void AVehiclePawn::TurnRearLights(bool value)
{
	RearLeftLight->SetVisibility(value);
	RearCenterLight->SetVisibility(value);
	RearRightLight->SetVisibility(value);
}

void AVehiclePawn::IncreasedSmokeExhaust()
{
	NS_ExhaustLeft->SetFloatParameter(FName("SpawnRate"), 350);
	NS_ExhaustRight->SetFloatParameter(FName("SpawnRate"), 350);
}

void AVehiclePawn::DecreasedSmokeExhaust()
{
	NS_ExhaustLeft->SetFloatParameter(FName("SpawnRate"), 30);
	NS_ExhaustRight->SetFloatParameter(FName("SpawnRate"), 30);
}

void AVehiclePawn::SwitchCamera()
{
	ActiveCameraIndex = (ActiveCameraIndex + 1) % 4;
	FRotator NewControlRotation = Controller->GetControlRotation();

	switch (ActiveCameraIndex)
	{
	case 0:
		Camera1->SetActive(true);
		Camera4->SetActive(false);
		NewControlRotation.Yaw = GetActorRotation().Yaw;
		NewControlRotation.Pitch = GetActorRotation().Pitch;
		Controller->SetControlRotation(NewControlRotation);
		break;
	case 1:
		Camera2->SetActive(true);
		Camera1->SetActive(false);
		NewControlRotation.Yaw = GetActorRotation().Yaw;
		NewControlRotation.Pitch = GetActorRotation().Pitch;
		Controller->SetControlRotation(NewControlRotation);
		break;
		
	case 2:
		Camera3->SetActive(true);
		Camera2->SetActive(false);
		break;	
	case 3:
		Camera4->SetActive(true);
		Camera3->SetActive(false);
		break;
	}
}

void AVehiclePawn::UpdateSteeringWheelRotation(float steeringInput)
{
	FRotator NewRotation = FRotator(0.f, 0.0f, SteeringInput * 45.f);
	SteeringWheelMesh->SetRelativeRotation(NewRotation);
}
