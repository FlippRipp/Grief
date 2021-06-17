#include "PickupableObject.h"
#include "FunnyDreamGame/Player/FGInteractionComponent.h"

APickupableObject::APickupableObject() : Super()
{

}

void APickupableObject::Interact(UFGInteractionComponent* Interacter)
{
	bIsCurrentlyPickedup = true;
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionProfileName("NoCollision");

	Interacter->PickupObject(this);
}

void APickupableObject::UnInteract(UFGInteractionComponent* Interacter)
{
	bIsCurrentlyPickedup = false;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionProfileName("PhysicsActor");

	Interacter->DropObject();
}
