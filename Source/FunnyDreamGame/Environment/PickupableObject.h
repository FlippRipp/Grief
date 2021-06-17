// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "PickupableObject.generated.h"

UCLASS()
class FUNNYDREAMGAME_API APickupableObject : public AInteractableObject
{
	GENERATED_BODY()
	//Methods:
public:
	APickupableObject();

	virtual void Interact(UFGInteractionComponent* Interacter) override;
	virtual void UnInteract(UFGInteractionComponent* Interacter) override;
protected:

	//Variables:
public:

protected:
	UPROPERTY(EditAnywhere)
	bool bIsCurrentlyPickedup = false;	

};
