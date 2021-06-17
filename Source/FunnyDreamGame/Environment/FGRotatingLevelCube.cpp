// Fill out your copyright notice in the Description page of Project Settings.


#include "FGRotatingLevelCube.h"
#include "FunnyDreamGame/Gamemodes/BoxRotationHandler.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFGRotatingLevelCube::AFGRotatingLevelCube()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxPivot = CreateDefaultSubobject<USceneComponent>(TEXT("BoxPivot"));
	BoxPivot->SetupAttachment(RootComponent);
}

void AFGRotatingLevelCube::QueueRotation(FRotator Rotation)
{
	GoalRotation += Rotation;
	RotationQueue.Add(Rotation.Quaternion());
	OnCubeRotation();
}

void AFGRotatingLevelCube::RegisterRotatorCube(ARotatorCube* Caller)
{
	if(RotatorCubes.Contains(Caller))
		return;
	RotatorCubes.Add(Caller);
}

TArray<ARotatorCube*> AFGRotatingLevelCube::GetRotatorCubes()
{
	return RotatorCubes;
}

void AFGRotatingLevelCube::BeginPlay()
{
	Super::BeginPlay();

	GoalRotation = GetActorRotation();
	
	AGameModeBase* gameMode = UGameplayStatics::GetGameMode(this);
	UActorComponent* component = gameMode->GetComponentByClass(UBoxRotationHandler::StaticClass());
	UBoxRotationHandler* boxRotator = Cast<UBoxRotationHandler>(component);
	if(boxRotator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RotatingLevelCube could not find the BoxRotationHandlerComponent on the assigned GameMode"));
		return;
	}

	boxRotator->RegisterCube(this, BoxNumber);
	
}

void AFGRotatingLevelCube::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	if(RotationQueue.Num() < 1)
	{
		return;
	}
		
	RotateCube(DeltaSeconds);
}

void AFGRotatingLevelCube::RotateCube(float DeltaSeconds)
{
	float rotationTime = RotationFraction + (RotationSpeed * DeltaSeconds);
	if(rotationTime > 1)
	{
		rotationTime -= 1;
		float diff = ((RotationSpeed * DeltaSeconds) - rotationTime);
		FRotator diffRotation = RotationQueue[0].Rotator() * diff;	
		AddActorWorldRotation(diffRotation);
		RotationFraction += RotationSpeed * DeltaSeconds;
	}
	else
	{
		RotationFraction += RotationSpeed * DeltaSeconds;
		FRotator diffRotation = RotationQueue[0].Rotator() * (RotationSpeed * DeltaSeconds);	
		AddActorWorldRotation(diffRotation);
	}
	
	if(RotationFraction >= 1)
	{
		RotationQueue.RemoveAt(0);
		RotationFraction = 0.0f;
	}
}	
