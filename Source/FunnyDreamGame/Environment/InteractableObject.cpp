// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

AInteractableObject::AInteractableObject()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    	
    HoverHighlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoverHighlightMesh"));
    HoverHighlightMesh->SetupAttachment(Mesh);
    
    HoverHighlightMesh->SetVisibility(false);
}

void AInteractableObject::Interact(UFGInteractionComponent* Interacter)
{
	
}

void AInteractableObject::UnInteract(UFGInteractionComponent* Interacter)
{
	
}

void AInteractableObject::Highlight()
{
	HoverHighlightMesh->SetVisibility(true);
}

void AInteractableObject::UnHighlight()
{
	HoverHighlightMesh->SetVisibility(false);
}


