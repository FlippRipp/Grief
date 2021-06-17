// Fill out your copyright notice in the Description page of Project Settings.


#include "FGMovementComponent.h"

#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


UFGMovementComponent::UFGMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFGMovementComponent::MoveActor(float deltaTime)
{	
	FHitResult MoveHit;
	FHitResult GravityHit;

	
	FVector MoveDirection = FVector::ZeroVector;
	MoveDirection.X = MovementInput.X;
	MoveDirection.Y = MovementInput.Y;
	MoveDirection = MoveDirection.GetSafeNormal();


	float GravityD = FMath::Sign(FVector::DotProduct(GravityDirection, GetOwner()->GetActorUpVector()));
	if(FMath::Sign(GravitySpeed) != GravityD)
	{
		//GravitySpeed = 0;
	}
	GravitySpeed += GravityD * GravityAccel * deltaTime;

	FVector Gravity = FVector(0, 0, GravitySpeed);

	FVector DeltaToMove = (MoveDirection * MaxSpeed) * deltaTime;
	DeltaToMove = GetOwner()->GetTransform().TransformVector(DeltaToMove);
	float distanceToMove = DeltaToMove.Size();
	FVector GravityToMove = Gravity * deltaTime;

	UE_LOG(LogTemp, Log, TEXT("Movement(%f, %f, %f)"), GetOwner()->GetActorRotation().Yaw, GetOwner()->GetActorRotation().Pitch, GetOwner()->GetActorRotation().Roll)

	bIsOnGround = false;

	// Calculations for step noise
	MovedSinceLastStep += distanceToMove;
	LengthMoved += distanceToMove;
	if(MovedSinceLastStep > StepLength)
	{
		OnStepTaken.Broadcast();
		MovedSinceLastStep -= StepLength;
	}
	BobCamera(deltaTime);
	
	for(int i = 0; i < 5; i++)
	{
		GetOwner()->AddActorWorldOffset(DeltaToMove, true, &MoveHit);
		GetOwner()->AddActorWorldOffset(GravityToMove, true, &GravityHit);

		DeltaToMove -= DeltaToMove * MoveHit.Time;

		
		
		if(GravityHit.bBlockingHit)
		{
			// UE_LOG(LogTemp, Log, TEXT("Dot: %f, Cos Angle: %f"), FVector::DotProduct(GravityHit.ImpactNormal, -Gravity.GetSafeNormal()), MaxSlope)
			
			if(FVector::DotProduct(GravityHit.ImpactNormal, -Gravity.GetSafeNormal()) < MaxSlope)
			{
				GravityToMove -= FVector::DotProduct(GravityToMove, GravityHit.Normal) * GravityHit.Normal;
				
				if(!bIsFalling)
				{
					bIsFalling = true;
					OnPlayerStartFalling.Broadcast();
				}
			}
			else
			{
				// UE_LOG(LogTemp, Log, TEXT("On Non-Slide ground"))
				GravityToMove = FVector::ZeroVector;
				GravitySpeed = 0;
				
				if(bIsFalling)
				{
					bIsFalling = false;
					OnPlayerStopFalling.Broadcast();
				}
			}
			// UE_LOG(LogTemp, Log, TEXT("Gravity hit? :´)"));
		}
		else
		{
			if(!bIsFalling)
			{
				bIsFalling = true;
				OnPlayerStartFalling.Broadcast();
			}
			// UE_LOG(LogTemp, Log, TEXT("Gravity not hit? :/"));
		}
		
		
		// UE_LOG(LogTemp, Log, TEXT("hit.Time : %f"), hit.Time)

		if(MoveHit.bBlockingHit)
		{
			// UE_LOG(LogTemp, Log, TEXT("We are Hitting something"))
			if(MoveHit.bStartPenetrating)
			{
				// UE_LOG(LogTemp, Log, TEXT("We are In something"))

				FVector DepenVector = MoveHit.Normal * (MoveHit.PenetrationDepth + 0.1f);
				GetOwner()->AddActorWorldOffset(DepenVector);
			}

			DeltaToMove -= FVector::DotProduct(DeltaToMove, MoveHit.Normal) * MoveHit.Normal;
        }
	}
}

void UFGMovementComponent::StartSprinting()
{
	MaxSpeed = SprintSpeed;
}

void UFGMovementComponent::StopSprinting()
{
	MaxSpeed = WalkSpeed;
}


// Called when the game starts
void UFGMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	MaxSpeed = WalkSpeed;

	CameraShakeOffset = Cast<APlayerPawn>(GetOwner())->CameraShakeOffset;
	// ...
}

void UFGMovementComponent::BobCamera(float DeltaSeconds)
{
	float waviness = CameraBobHeight * sin((3.14/(StepLength*0.5f))*LengthMoved);
	FVector bobPosition = FVector::ZeroVector;
	bobPosition.Z = waviness;
	CameraShakeOffset->SetRelativeLocation(bobPosition);
	// CameraShakeOffset->AddLocalOffset(bobPosition);
}


// Called every frame
void UFGMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bShouldMove)
		return;
	MoveActor(DeltaTime);
	// ...
}
