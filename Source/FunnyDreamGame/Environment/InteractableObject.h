// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

class UFGInteractionComponent;
class UStaticMeshComponent;

UCLASS()
class FUNNYDREAMGAME_API AInteractableObject : public AActor
{
	GENERATED_BODY()

public:
	AInteractableObject();
	virtual void Interact(UFGInteractionComponent* Interacter);
	virtual void UnInteract(UFGInteractionComponent* Interacter);

	virtual void Highlight();

	virtual void UnHighlight();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HoverHighlightMesh;

};
