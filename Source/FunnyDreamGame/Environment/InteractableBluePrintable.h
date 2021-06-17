// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "InteractableBluePrintable.generated.h"

/**
 * 
 */


UCLASS()
class FUNNYDREAMGAME_API AInteractableBluePrintable : public AInteractableObject
{
	GENERATED_BODY()

	public:
	virtual void Interact(UFGInteractionComponent* Interacter) override;
	virtual void UnInteract(UFGInteractionComponent* Interacter) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract(UFGInteractionComponent* Interacter);
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnInteract(UFGInteractionComponent* Interacter);
};
