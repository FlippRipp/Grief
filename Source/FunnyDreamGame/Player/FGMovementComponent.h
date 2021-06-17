// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStartFalling);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStopFalling);

class UCameraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStepDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNYDREAMGAME_API UFGMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFGMovementComponent();
	FVector2D MovementInput;
	FVector CurrentVelocity;
	void MoveActor(float deltaTime);
	void StartSprinting();
	void StopSprinting();

	UPROPERTY(EditAnywhere)
	FVector GravityDirection = FVector(0, 0, -1);
	UPROPERTY(EditAnywhere)
	float GravityAccel = 476.f;
	float GravitySpeed;
	
	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 4000;
	UPROPERTY(EditAnywhere)  
	float MaxRetardation = 4000;

	bool bIsFalling = false;

    UPROPERTY(BlueprintAssignable, Category="Custom")
    FOnPlayerStartFalling OnPlayerStartFalling;
    
     UPROPERTY(BlueprintAssignable, Category="Custom")
    FOnPlayerStopFalling OnPlayerStopFalling;
    
    
	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1500.0f;
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
	float MaxSlope = 1;

	UPROPERTY(EditAnywhere)
	float StepLength = 70.0f;

	UPROPERTY(EditAnywhere)
	float CameraBobHeight = 50.0f;
	
	bool bIsOnGround;
	
	float MaxSpeed = 1000;

	UPROPERTY(BlueprintAssignable)
	FStepDelegate OnStepTaken;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void BobCamera(float DeltaSeconds);
	
	float MovedSinceLastStep = 0;
	float LengthMoved = 0;

	UPROPERTY()
	USceneComponent* CameraShakeOffset;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool bShouldMove = true;
		
};