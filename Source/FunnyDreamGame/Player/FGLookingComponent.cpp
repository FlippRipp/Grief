#include "FGLookingComponent.h"

#include "Camera/CameraComponent.h"

UFGLookingComponent::UFGLookingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGLookingComponent::LookUp(float DeltaTime)
{
	FRotator deltaPitch = FRotator::ZeroRotator;
	deltaPitch.Pitch = DeltaTime * PitchSpeed * LookingInput.Y;

	FRotator cameraRotation = LookingCamera->GetRelativeRotation();
	cameraRotation.ClampAxis(cameraRotation.Pitch);

	LookingCamera->AddLocalRotation(deltaPitch);
	
	FRotator CameraRot = LookingCamera->GetRelativeRotation();

	UE_LOG(LogTemp, Log, TEXT("pitch; %f, deltaPitch: %f, limitUpper: %f, limitLower: %f"), CameraRot.Pitch, deltaPitch.Pitch, 80 - CameraRot.Pitch, -80 - CameraRot.Pitch)

	if(bPitchIsClamped)
	{
		if(deltaPitch.Pitch > 0)
		{
			//UE_LOG(LogTemp, Log, TEXT("deltapitch +"))
			if(deltaPitch.Pitch > PitchMax - CameraRot.Pitch)
			{
				UE_LOG(LogTemp, Log, TEXT("deltapitch + clamp"))
				CameraRot = cameraRotation;
			}
		}
		else if(deltaPitch.Pitch < 0)
		{
			if(deltaPitch.Pitch < -PitchMax - CameraRot.Pitch)
			{
				CameraRot = cameraRotation;
			}
		}
	}



	if(bPitchIsClamped)
	{
		CameraRot.Pitch = FMath::Clamp(CameraRot.Pitch, -PitchMax, PitchMax);
		CameraRot.Roll = 0;
	}

	LookingCamera->SetRelativeRotation(CameraRot);
}

void UFGLookingComponent::LookRight(float DeltaTime)
{ 
	FRotator deltaYaw = FRotator::ZeroRotator;
	deltaYaw.Yaw = DeltaTime * YawSpeed * LookingInput.X;

	GetOwner()->GetRootComponent()->AddWorldRotation(deltaYaw);

	FRotator PlayerRot = GetOwner()->GetRootComponent()->GetComponentRotation();

	if(bYawIsClamped)
	{
		PlayerRot.Yaw = FMath::Clamp(PlayerRot.Yaw, -YawMax, YawMax);
		PlayerRot.Roll = 0;
		PlayerRot.Pitch = 0;

	}
	GetOwner()->GetRootComponent()->SetWorldRotation(PlayerRot);

	
}

void UFGLookingComponent::SetCamera(UCameraComponent* pCamera)
{
	LookingCamera = pCamera;
}

void UFGLookingComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UFGLookingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LookUp(DeltaTime);
	LookRight(DeltaTime);
}

