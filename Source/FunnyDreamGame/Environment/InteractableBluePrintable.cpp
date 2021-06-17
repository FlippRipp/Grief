// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBluePrintable.h"

void AInteractableBluePrintable::Interact(UFGInteractionComponent* Interacter)
{
	UE_LOG(LogTemp, Log, TEXT("interact in blueprintable"))
	OnInteract(Interacter);
}

void AInteractableBluePrintable::UnInteract(UFGInteractionComponent* Interacter)
{
	OnUnInteract(Interacter);
}
