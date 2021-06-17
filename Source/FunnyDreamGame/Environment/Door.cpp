// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "KeyItem.h"
#include "FunnyDreamGame/Player/FGInteractionComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ADoor::ADoor() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsRotating) return;

	Step += RotationSpeed / 90 * DeltaTime;

	SetActorRotation(FMath::Lerp(FromRotation.Quaternion(), TargetRotation.Quaternion(), Step));

	if(Step >= 1)
	{
		SetActorRotation(TargetRotation);
		bIsRotating = false;
	}
}

void ADoor::OpenDoor()
{
	bIsOpen = true;
	FromRotation = ClosedRotation;
	TargetRotation = OpenRotation;
	bIsRotating = true;
	Step = 0;
	UE_LOG(LogTemp, Log, TEXT("StartRotation(%f, %f, %f)"), StartRotation.Pitch, StartRotation.Yaw, StartRotation.Roll);
	UE_LOG(LogTemp, Log, TEXT("TargetRotation(%f, %f, %f)"), TargetRotation.Pitch, TargetRotation.Yaw, TargetRotation.Roll);
}

void ADoor::CloseDoor()
{
	bIsOpen = false;
	FromRotation = OpenRotation;
	TargetRotation = ClosedRotation;
	bIsRotating = true;
	Step = 0;

}

void ADoor::LockDoor()
{
	bIsLocked = true;
}

void ADoor::UnlockDoor()
{
	bIsLocked = false;
}

// void ADoor::OnPlayerInteract(UFGInteractionComponent* Interacter)
// {
// 		if(bIsKeyLocked)
// 	{
// 		if(Interacter->bHasKey && !bIsOpen)
// 		{
// 			KeyItem = Interacter->KeyItem;
// 			KeyItem->UnInteract(Interacter);
// 			
// 			KeyItem->Mesh->SetSimulatePhysics(false);
// 			KeyItem->Mesh->SetCollisionProfileName("NoCollision");
// 			KeyItem->Mesh->SetVisibility(false);
// 			OnOpenDoorInteract();
// 			OpenDoor();
// 		}
// 		else if(bIsOpen)
// 		{
// 			if(Interacter->CurrentInteractable != nullptr) Interacter->CurrentInteractable->UnInteract(Interacter);
// 			
// 			if(KeyItem != nullptr)
// 			{
// 				KeyItem->Mesh->SetVisibility(true);
// 				KeyItem->Interact(Interacter);
// 			}
//
// 			CloseDoor();
// 		}
// 		OnLockedDoorInteract();
// 	}
// 	else if(bIsLocked)
// 	{
// 		OnLockedDoorInteract();
// 		return;
// 	}
// 	else if(bIsOpen)
// 	{
// 		OnCloseDoorInteract();
// 		CloseDoor();
// 	}
// 	else
// 	{
// 		OnOpenDoorInteract();
// 		OpenDoor();
// 	}
// }

void ADoor::Interact(UFGInteractionComponent* Interacter)
{
	if(bIsKeyLocked)
	{
		if(Interacter->bHasKey && !bIsOpen)
		{
			// KeyItem = Interacter->KeyItem;
			// KeyItem->UnInteract(Interacter);
			//
			// KeyItem->Mesh->SetSimulatePhysics(false);
			// KeyItem->Mesh->SetCollisionProfileName("NoCollision");
			// KeyItem->Mesh->SetVisibility(false);
			OnOpenDoorInteract();
			OpenDoor();
		}
		else if(bIsOpen)
		{
			// if(Interacter->CurrentInteractable != nullptr) Interacter->CurrentInteractable->UnInteract(Interacter);
			//
			// if(KeyItem != nullptr)
			// {
			// 	KeyItem->Mesh->SetVisibility(true);
			// 	KeyItem->Interact(Interacter);
			// }

			OnCloseDoorInteract();
			CloseDoor();
		}
		else if(!Interacter->bHasKey && !bIsOpen)
		{
			OnKeyLockedDoorInteract();
		}
	}
	else if(bIsLocked)
	{
		OnLockedDoorInteract();
		return;
	}
	else if(bIsOpen)
	{
		OnCloseDoorInteract();
		CloseDoor();
	}
	else
	{
		OnOpenDoorInteract();
		OpenDoor();
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();	
	ClosedRotation = GetTransform().TransformRotation(ClosedRotation.Quaternion()).Rotator();
	OpenRotation = GetTransform().TransformRotation(OpenRotation.Quaternion()).Rotator();
}