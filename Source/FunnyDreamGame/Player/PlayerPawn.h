// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class UCapsuleComponent;

class UFGInteractionComponent;
class UFGMovementComponent;
class UFGGravityFlipComponent;
class UFGLookingComponent;

UENUM()
enum PlayerLevelState
{
	DENIAL,
	OFFICE,
	BARGAINING,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogNextInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogPrevInput);

UCLASS()
class FUNNYDREAMGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	APlayerPawn();
	void HandleMoveForward(float value);
	void HandleMoveRight(float value);
	void HandleLookUp(float value);
	void HandleLookRight(float value);
	void HandleSprintOn();
	void HandleSprintOff();
	void HandleFlipGravity();
	void HandleRotateCubeUp();
	void HandleRotateCubeDown();
	void HandleRotateCubeLeft();
	void HandleRotateCubeRight();
	void HandlePickupRightRotation(float value);
	void HandlePickupUpRotation(float value);
	void HandleDialogNext();
	void HandleDialogPrev();
	
	void PlayerInteract();
	void ToggleMovement(bool Activate);

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CameraShakeOffset;
	
	UPROPERTY(VisibleAnywhere)
	UFGMovementComponent* MovementComponent;
	UPROPERTY(VisibleAnywhere)
	UFGGravityFlipComponent* GravityFlipComponent;
	UPROPERTY(VisibleAnywhere)
	UFGLookingComponent* LookingComponent;
	UPROPERTY(VisibleAnywhere)
	UFGInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<PlayerLevelState> CurrentState = DENIAL;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* PickupAttachment;
	
	UFUNCTION(BlueprintCallable)
	void SetupInputForLevel(PlayerLevelState LevelToEnter);
	
	UPROPERTY(EditAnywhere)
	bool IsCameraGravityFlip = false;

	bool IsGravityReversed = false;
	float CameraHeight;
	float CameraHeightLerpStep = 0;

	UPROPERTY(EditAnywhere)
	bool bCanGravityReverse = true;

	UPROPERTY(BlueprintAssignable)
	FDialogNextInput DialogNextInput;
	
	UPROPERTY(BlueprintAssignable)
	FDialogPrevInput DialogPrevInput;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);

	void ClearInputBindings();	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void RestartLevelOnDeath();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void DestroyPlayerInputComponent() override;
};
