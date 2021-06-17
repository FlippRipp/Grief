// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "DestructibleObject.generated.h"

class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroyDelegate);

UCLASS()
class FUNNYDREAMGAME_API ADestructibleObject : public AInteractableObject
{
	GENERATED_BODY()

	//Methods:
public:
	ADestructibleObject();
	virtual void Interact(UFGInteractionComponent* Interacter) override;
protected:

	//Variables:
public:

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<AActor> ExplodingMeshActor;

	UPROPERTY(BlueprintAssignable)
	FDestroyDelegate OnObjectDestroyed;

	UPROPERTY(EDitAnywhere)
	bool bShouldReportWall = true;

	protected:
	
};
