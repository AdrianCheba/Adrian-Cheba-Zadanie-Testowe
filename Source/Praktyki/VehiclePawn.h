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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* SteeringWheelMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPointLightComponent* RearLeftLight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPointLightComponent* RearCenterLight;	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPointLightComponent* RearRightLight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNiagaraComponent* NS_RR_Trail;	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNiagaraComponent* NS_RL_Trail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNiagaraComponent* NS_FR_Trail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UNiagaraComponent* NS_FL_Trail;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* BumperFront;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* Body;	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* HoodFront;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* FenderRight;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* FenderLeft;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* DoorRight;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* DoorLeft;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* Window;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* BootRear;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* BumperRear;	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* SpoilerBack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
	class UMaterialInterface* DamageMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
	class UMaterialInterface* DamageLightMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
	class UMaterialInterface* DamageWindowMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DamageTake;

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
	void RestartLevel();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
