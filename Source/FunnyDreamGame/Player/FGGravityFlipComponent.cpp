// Fill out your copyright notice in the Description page of Project Settings.


#include "FGGravityFlipComponent.h"


#include "PlayerPawn.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UFGGravityFlipComponent::UFGGravityFlipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFGGravityFlipComponent::BeginPlay()
{
	Super::BeginPlay();
	Player =  Cast<APlayerPawn>(GetOwner());
	if(Player != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Is Player true"))
		IsPlayer = true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Is Player false"))
	}
	// ...	
}


// Called every frame
void UFGGravityFlipComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator Rotation = GetOwner()->GetActorRotation();

	//UE_LOG(LogTemp, Log, TEXT("Rotation (%f, %f, %f)"), Rotation.Roll, Rotation.Pitch, Rotation.Yaw)


	//Flip to upside down
	if (IsGravityFlipped && IsFlipTransition)
	{
		if (FlipStep >= 1)
		{
			FlipStep = 1;
			IsFlipTransition = false;
			Rotation.Roll = 180;
			if(IsPlayer) Player->IsGravityReversed = true;
		}
		else
		{
			FlipStep += DeltaTime / FlipTransitionTime;
			Rotation.Roll = FMath::Lerp(0, 180, FlipStep);
		}
	}

	//Flip to normal
	if (!IsGravityFlipped && IsFlipTransition)
	{
		if (FlipStep <= 0)
		{
			FlipStep = 0;
			IsFlipTransition = false;
			Rotation.Roll = 0;
			if(IsPlayer) Player->IsGravityReversed = false;
		}
		else
		{
			FlipStep -= DeltaTime / FlipTransitionTime;
			Rotation.Roll = FMath::Lerp(0, 180, FlipStep);
		}
	}
	
	if(IsFlipTransition)
	{
		GetOwner()->SetActorRotation(Rotation);
	}
}

void UFGGravityFlipComponent::FlipGravity()
{
	IsGravityFlipped = !IsGravityFlipped;
	IsFlipTransition = true;
}
