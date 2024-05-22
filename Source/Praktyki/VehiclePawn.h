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
	class UCameraComponent* Camera;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAudioComponent* EngineSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPointLightComponent* RearLeftLight;	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPointLightComponent* RearRightLight;

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
	class UInputAction* ToggleCameraAction;	

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* RestartAction;

	
private:
	void MoveForward(const FInputActionValue& value);
	void OnBrakePressed(const FInputActionValue& value);
	void OnBrakeReleased(const FInputActionValue& value);
	void LookAround(const FInputActionValue& value);
	void LookUpDown(const FInputActionValue& value);
	void Steering(const FInputActionValue& value);
	void SteeringReleased();
	void OnHandBrakePressed();
	void OnHandBrakeReleased();
	void OnThrottleReleased();
	void TurnRearLights(bool value);
};
