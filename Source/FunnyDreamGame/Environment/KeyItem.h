// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupableObject.h"
#include "KeyItem.generated.h"

class UStaticMeshComponent;

UCLASS()
class FUNNYDREAMGAME_API AKeyItem : public APickupableObject
{
	GENERATED_BODY()

	//Methods:
public:
	AKeyItem();
	
	virtual void Interact(UFGInteractionComponent* Interacter) override;
	virtual void UnInteract(UFGInteractionComponent* Interacter) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnKeyPickup();
};
