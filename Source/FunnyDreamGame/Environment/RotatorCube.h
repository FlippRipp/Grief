// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InteractableObject.h"
#include "RotatorCube.generated.h"



class UStaticMeshComponent;
class AFGRotatingLevelCube;

UCLASS()
class FUNNYDREAMGAME_API ARotatorCube : public AInteractableObject
{
	GENERATED_BODY()

	//Methods:
public:
	ARotatorCube();
	void QueueRotation(FRotator Rotation);
protected:
	virtual void Interact(UFGInteractionComponent* Interacter) override;
	virtual void UnInteract(UFGInteractionComponent* Interacter) override;
	virtual void BeginPlay() override;

	void RotateCube(float DeltaSeconds);
	
	virtual void Tick(float DeltaSeconds) override;
	
	
	void SetCube();

	//Variables:
public:
	UPROPERTY(EditAnywhere)
	int BoxNumber = 1;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 5.0f;

	bool bIsLocked = true;

	UPROPERTY(EditAnywhere)
	bool bIsRotated = false;

	UFUNCTION(BlueprintImplementableEvent)
    void OnCubeRotation();

protected:
	UPROPERTY()
	AFGRotatingLevelCube* LevelCube;

	UPROPERTY()
	TArray<ARotatorCube*> OtherCubes;

	float rotationFraction = 0.0f;
	TArray<FRotator> RotationQueue;

	FTransform StartTransform;
	FVector StartForward;
	FVector StartRight;
};
