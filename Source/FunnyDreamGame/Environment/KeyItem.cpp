#include "KeyItem.h"
#include "FunnyDreamGame/Player/FGInteractionComponent.h"

AKeyItem::AKeyItem() : Super()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AKeyItem::Interact(UFGInteractionComponent* Interacter)
{
	// Super::Interact(Interacter);
	//
	// Interacter->bShouldRotatePickup = false;
	OnKeyPickup();
	Interacter->bHasKey = true;
	 Mesh->SetSimulatePhysics(false);
	 Mesh->SetCollisionProfileName("NoCollision");
	 Mesh->SetVisibility(false);
	//Interacter->KeyItem = this;
	
}

void AKeyItem::UnInteract(UFGInteractionComponent* Interacter)
{
	// Super::UnInteract(Interacter);
	//
	// Interacter->bShouldRotatePickup = true;
	Interacter->bHasKey = false;
	//Interacter->KeyItem = nullptr;
}
