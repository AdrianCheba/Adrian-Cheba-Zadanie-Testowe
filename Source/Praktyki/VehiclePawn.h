// Copyright 2023 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "InputActionValue.h"
#include "VehiclePawn.generated.h"


UCLASS()
class PRAKTYKI_API AVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	AVehiclePawn();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera4;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAudioComponent* EngineSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNiagaraComponent* NS_ExhaustRight;	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNiagaraComponent* NS_ExhaustLeft;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UStaticMeshComponent* SteeringWheelMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UPointLightComponent* RearLeftLight;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UPointLightComponent* RearCenterLight;	
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UPointLightComponent* RearRightLight;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UNiagaraComponent* NS_RR_Trail;	
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UNiagaraComponent* NS_RL_Trail;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UNiagaraComponent* NS_FR_Trail;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UNiagaraComponent* NS_FL_Trail;

protected:
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* HandBrakeAction;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* ThrottleAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* BrakeAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookAroundAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookUpDownAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SteeringAction;	
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SwitchCameraAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* RestartAction;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* InteriorCameraLookAction;

	float SteeringInput;
	int ActiveCameraIndex;
	
private:
	void MoveForward(const FInputActionValue& value);
	void OnBrakePressed(const FInputActionValue& value);
	void OnBrakeReleased(const FInputActionValue& value);
	void LookAround(const FInputActionValue& value);
	void LookUpDown(const FInputActionValue& value);
	void InteriorCameraLook();
	void InteriorCameraLookReleased();
	void Steering(const FInputActionValue& value);
	void SteeringReleased();
	void OnHandBrakePressed();
	void OnHandBrakeReleased();
	void OnThrottleReleased();
	void TurnRearLights(bool value);
	void IncreasedSmokeExhaust();
	void DecreasedSmokeExhaust();
	void SwitchCamera();
	void UpdateSteeringWheelRotation(float steeringInput);
	void ActivateTrails(bool isHandbrake);
	void DeactivateTrails();
};
