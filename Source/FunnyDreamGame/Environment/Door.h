// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class AKeyItem;
UCLASS()
class FUNNYDREAMGAME_API ADoor : public AInteractableObject
{
	GENERATED_BODY()
	
public:	
	ADoor();

	UPROPERTY(EditAnywhere)
	bool bIsLocked;
	UPROPERTY(EditAnywhere)
	bool bIsKeyLocked;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 90;

	UPROPERTY()
	AKeyItem* KeyItem;
	FRotator StartRotation;
	
	FRotator TargetRotation;
	FRotator FromRotation;

	float Step;
	bool bIsRotating = false;

	UPROPERTY(EditAnywhere)
	FRotator OpenRotation = FRotator(0, 90, 0);
	UPROPERTY(EditAnywhere)
	FRotator ClosedRotation = FRotator(0, 0, 0);
	void OpenDoor();
	void CloseDoor();
	void LockDoor();
	void UnlockDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLockedDoorInteract();
	UFUNCTION(BlueprintImplementableEvent)
	void OnKeyLockedDoorInteract();
	UFUNCTION(BlueprintImplementableEvent)
	void OnOpenDoorInteract();
	UFUNCTION(BlueprintImplementableEvent)
	void OnCloseDoorInteract();

	// void OnPlayerInteract(UFGInteractionComponent* Interacter);

	virtual void Interact(UFGInteractionComponent* Interacter) override;
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	bool bIsOpen;

public:	
	virtual void Tick(float DeltaTime) override;

};
