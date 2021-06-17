#include "RotatorCube.h"

#include "FunnyDreamGame/Gamemodes/BoxRotationHandler.h"
#include "FunnyDreamGame/Player/FGInteractionComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

ARotatorCube::ARotatorCube() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	// CubeRotationPivot = CreateDefaultSubobject<USceneComponent>(TEXT("CubeRotationPivot"));

	// Mesh->SetupAttachment(CubeRotationPivot);
	//
	// HoverHighlightMesh->SetupAttachment(Mesh);
	//
	// RootComponent = CubeRotationPivot;

	// KeyHole = CreateDefaultSubobject<USceneComponent>(TEXT("KeyHole"));
	// KeyHole->SetupAttachment(RootComponent);
}

void ARotatorCube::QueueRotation(FRotator Rotation)
{
	if(LevelCube == nullptr
		|| OtherCubes.Num() == 0)
		SetCube();

	FRotator newRotation;

	FRotator startRotation = StartForward.Rotation();

    OnCubeRotation();


	if(bIsRotated)
	{
		newRotation.Pitch = Rotation.Roll;
		newRotation.Roll = -Rotation.Pitch;
		newRotation.Yaw = 0;
	}
	else
	{
		newRotation = Rotation;
	}
	

	// newRotation.Yaw += 90;
	// if(Rotation.Pitch > 5 || Rotation.Pitch < -5)
	// {
	// 	newRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(StartRight, -Rotation.Pitch);
	// }
	// else if(Rotation.Roll > 5 || Rotation.Roll < -5)
	// {
	// 	newRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(StartForward, -Rotation.Roll);
	// }

	LevelCube->QueueRotation(newRotation);
	for(auto cube : OtherCubes)
	{
		cube->RotationQueue.Add(newRotation);
	}
	RotationQueue.Add(newRotation);
}

// void ARotatorCube::OnPlayerInteract(UFGInteractionComponent* Interacter)
// {
// 		 if(!Interacter->bHasKey)
// 	 	return;
// 	
// 	 //Interacter->InsertKey(KeyHole);
// 	Interacter->ToggleMovement(false);
// 	Interacter->bHasCube = true;
// 	Interacter->CurrentCube = this;
// 	Interacter->bHasInteractable = true;
// 	//Interacter->CurrentInteractable = this;
// }
//
// void ARotatorCube::OnPlayerStopInteract(UFGInteractionComponent* Interacter)
// {
// 		Interacter->ToggleMovement(true);
// 		Interacter->bHasCube = false;
// 		Interacter->CurrentCube = nullptr;
// 		Interacter->bHasInteractable = false;
// 		Interacter->CurrentInteractable = nullptr;
// }

void ARotatorCube::Interact(UFGInteractionComponent* Interacter)
{
	// if(!Interacter->bHasKey)
	// 	return;
	
	// Interacter->InsertKey(KeyHole);
	Interacter->ToggleMovement(false);
	Interacter->bHasCube = true;
	Interacter->CurrentCube = this;
	Interacter->bHasInteractable = true;
	Interacter->CurrentInteractable = this;
}

void ARotatorCube::UnInteract(UFGInteractionComponent* Interacter)
{
	Interacter->ToggleMovement(true);
	Interacter->bHasCube = false;
	Interacter->CurrentCube = nullptr;
	Interacter->bHasInteractable = false;
	Interacter->CurrentInteractable = nullptr;

}

void ARotatorCube::BeginPlay()
{
	Super::BeginPlay();
	StartForward = RootComponent->GetForwardVector();
	StartRight = RootComponent->GetRightVector();

	AGameModeBase* gameMode = UGameplayStatics::GetGameMode(this);
	UActorComponent* component = gameMode->GetComponentByClass(UBoxRotationHandler::StaticClass());
	UBoxRotationHandler* boxRotator = Cast<UBoxRotationHandler>(component);
	if(boxRotator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RotatorCube could not find the BoxRotationHandlerComponent on the assigned GameMode"));
		return;
	}

	boxRotator->RegisterRotatorCube(this, BoxNumber);
}

void ARotatorCube::SetCube()
{
	AGameModeBase* gameMode = UGameplayStatics::GetGameMode(this);
	UActorComponent* component = gameMode->GetComponentByClass(UBoxRotationHandler::StaticClass());
	UBoxRotationHandler* boxRotator = Cast<UBoxRotationHandler>(component);
	if(boxRotator == nullptr)
		return;

	if(LevelCube == nullptr)
	{
		LevelCube = boxRotator->GetCube(BoxNumber);
	}

	if(OtherCubes.Num() == 0)
	{
		OtherCubes = boxRotator->GetRotatorCubes(BoxNumber);

		if(OtherCubes.Contains(this))
		{
			OtherCubes.Remove(this);
		}
	}
}

void ARotatorCube::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(RotationQueue.Num() < 1)
		return;
		
	RotateCube(DeltaSeconds);
}

void ARotatorCube::RotateCube(float DeltaSeconds)
{
	float rotationTime = rotationFraction + (RotationSpeed * DeltaSeconds);
	if(rotationTime > 1)
	{
		rotationTime -= 1;
		float diff = ((RotationSpeed * DeltaSeconds) - rotationTime);
		FRotator diffRotation = RotationQueue[0] * diff;
		Mesh->AddWorldRotation(diffRotation);
		rotationFraction += RotationSpeed * DeltaSeconds;
	}
	else
	{
		rotationFraction += RotationSpeed * DeltaSeconds;
		FRotator diffRotation = RotationQueue[0] * (RotationSpeed * DeltaSeconds);
		Mesh->AddWorldRotation(diffRotation);
	}
	
	if(rotationFraction >= 1)
	{
		RotationQueue.RemoveAt(0);
		rotationFraction = 0.0f;
	}
}	