#include "FGInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "FunnyDreamGame/Environment/InteractableObject.h"
#include "FunnyDreamGame/Environment/PickupableObject.h"
#include "FunnyDreamGame/Environment/RotatorCube.h"
#include "FGMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FunnyDreamGame//Environment/Door.h"

UFGInteractionComponent::UFGInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFGInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TryEnableHighlight();
	
	if(!bHasPickup)
		return;
	
	if(!RotationInput.IsNearlyZero(0.1f) && bShouldRotatePickup)
	{
		RotatePickup(DeltaTime);
	}

	
}

void UFGInteractionComponent::PickupObject(APickupableObject* Object)
{
	CurrentInteractable = Object;
	bHasPickup = true;
	// Object->GetRootComponent()->AttachToComponent(PickupAttachment, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Object->GetRootComponent()->AttachToComponent(PickupAttachment, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void UFGInteractionComponent::DropObject()
{
	if(CurrentInteractable == nullptr)
	{
		bHasPickup = bHasCube = true;
	}
	CurrentInteractable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	bHasPickup = false;
	CurrentInteractable = nullptr;
}

void UFGInteractionComponent::RotatePickup(float DeltaTime)
{
	if(!bHasPickup)
		return;
		
	FRotator newRotation = FRotator::ZeroRotator;

	newRotation.Pitch -= RotationInput.Y * (PitchSpeed * DeltaTime);
	newRotation.Roll += RotationInput.X * (RollSpeed * DeltaTime);
	
	CurrentInteractable->GetRootComponent()->AddLocalRotation(newRotation);
}

void UFGInteractionComponent::RotateCubeUp()
{
	if(!bHasCube)
		return;

	FRotator newRotation = FRotator::ZeroRotator;
	newRotation.Pitch = -90.0f;
	CurrentCube->QueueRotation(newRotation);
}

void UFGInteractionComponent::RotateCubeDown()
{
	if(!bHasCube)
		return;

	FRotator newRotation = FRotator::ZeroRotator;
	newRotation.Pitch = 90.0f;
	CurrentCube->QueueRotation(newRotation);
}

void UFGInteractionComponent::RotateCubeLeft()
{
	if(!bHasCube)
		return;

	FRotator newRotation = FRotator::ZeroRotator;
	newRotation.Roll = -90.0f;
	CurrentCube->QueueRotation(newRotation);
}

void UFGInteractionComponent::RotateCubeRight()
{
	if(!bHasCube)
		return;

	FRotator newRotation = FRotator::ZeroRotator;
	newRotation.Roll = 90.0f;
	CurrentCube->QueueRotation(newRotation);
}

void UFGInteractionComponent::SetupComponent(UCameraComponent* Camera, USceneComponent* OwnerPickupAttachment)
{
	RayCamera = Camera;
	PickupAttachment = OwnerPickupAttachment;
}

void UFGInteractionComponent::Interact()
{
	if (CurrentInteractable != nullptr)
	{
		CurrentInteractable->UnInteract(this);
		return;
	}

	AInteractableObject* InteractableObject = CheckForInteractable();

	if(InteractableObject == nullptr)
	{
		return;
	}
	
	InteractableObject->Interact(this);
}

AInteractableObject* UFGInteractionComponent::CheckForInteractable()
{
	AInteractableObject* InteractableObject = nullptr;
	
	TArray<AActor*> ShitToIgnore;
	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(this, RayCamera->GetComponentLocation(),
		RayCamera->GetComponentLocation() + RayCamera->GetForwardVector() * InteractionDistance,
		UEngineTypes::ConvertToTraceType(ECC_Pawn), false, ShitToIgnore,
		EDrawDebugTrace::None, Hit, true);
	if(Hit.bBlockingHit)
	{
		auto* HitTarget = Hit.GetActor();
		if (HitTarget == nullptr)
		{
			return nullptr;
		}
		InteractableObject = Cast<AInteractableObject>(HitTarget);
	}
	return InteractableObject;
}

void UFGInteractionComponent::TryEnableHighlight()
{
	AInteractableObject* Interactable = CheckForInteractable();

	if(Interactable)
	{
		if(CurrentHighlightedObject != Interactable)
		{
			if(CurrentHighlightedObject)
				CurrentHighlightedObject->UnHighlight();
			
			Interactable->Highlight();
			CurrentHighlightedObject = Interactable;
		}
	}
	else if (CurrentHighlightedObject)
	{
		CurrentHighlightedObject->UnHighlight();
		CurrentHighlightedObject = nullptr;
	}
}

void UFGInteractionComponent::ToggleMovement(bool bActivate)
{
	UActorComponent* comp =  GetOwner()->GetComponentByClass(UFGMovementComponent::StaticClass());
	UFGMovementComponent* moveComp = Cast<UFGMovementComponent>(comp);
	if(moveComp != nullptr)
	{
		moveComp->bShouldMove = bActivate;
	}
}
