// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGInteractionComponent.generated.h"

class UCameraComponent;
class AInteractableObject;
class APickupableObject;
class ARotatorCube;
class AKeyItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNYDREAMGAME_API UFGInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFGInteractionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PickupObject(APickupableObject* Object);
	void DropObject();
	void RotatePickup(float DeltaTime);
	void RotateCubeUp();
	void RotateCubeDown();
	void RotateCubeLeft();
	void RotateCubeRight();
	
	void SetupComponent(UCameraComponent* Camera, USceneComponent* OwnerPickupAttachment);
	void Interact();

	AInteractableObject* CheckForInteractable();

	void TryEnableHighlight();

	void ToggleMovement(bool bActivate);
protected:
	virtual void BeginPlay() override;
public:
	FVector2D RotationInput = FVector2D::ZeroVector;	
	bool bHasInteractable = false;
	bool bHasPickup = false;
	bool bHasCube = false;
	bool bShouldRotatePickup = true;
	bool bHasKey = false;
	bool bIsKeyInUse;
	
	UPROPERTY(EditAnywhere)
	float InteractionDistance = 300.0f;

	UPROPERTY(EditAnywhere)
	float PitchSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	float RollSpeed = 100.0f;

	UPROPERTY()
	ARotatorCube* CurrentCube;
	UPROPERTY()
	AKeyItem* KeyItem;
	UPROPERTY()
	AInteractableObject* CurrentInteractable;
	UPROPERTY()
	AInteractableObject* CurrentHighlightedObject;
protected:
	UPROPERTY()
	UCameraComponent* RayCamera;
	UPROPERTY()
	USceneComponent* PickupAttachment;
};
