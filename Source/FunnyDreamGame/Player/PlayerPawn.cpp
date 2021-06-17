#include "PlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "FGMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FunnyDreamGame/Environment/InteractableObject.h"
#include "FGGravityFlipComponent.h"
#include "FGLookingComponent.h"
#include "FGInteractionComponent.h"
#include "Math/UnrealMathUtility.h"



APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCapsule"));
	RootComponent = Capsule;

	CameraShakeOffset = CreateDefaultSubobject<USceneComponent>(TEXT("CameraShakeOffset"));
	CameraShakeOffset->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraShakeOffset);
	
	MovementComponent = CreateDefaultSubobject<UFGMovementComponent>(TEXT("MovementComponent"));
	GravityFlipComponent = CreateDefaultSubobject<UFGGravityFlipComponent>(TEXT("GravityFlipComponet"));
	LookingComponent = CreateDefaultSubobject<UFGLookingComponent>(TEXT("LookingComponent"));
	LookingComponent->SetCamera(Camera);
	PickupAttachment = CreateDefaultSubobject<USceneComponent>(TEXT("PickupAttachment"));
	PickupAttachment->SetupAttachment(Camera);
	InteractionComponent = CreateDefaultSubobject<UFGInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->SetupComponent(Camera, PickupAttachment);
	
	Capsule->OnComponentHit.AddDynamic(this, &APlayerPawn::OnCompHit);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerPawn::OnBeginOverlap);
}

void APlayerPawn::SetupInputForLevel(PlayerLevelState LevelToEnter)
{
	ClearInputBindings();
	switch(LevelToEnter)
	{
		case DENIAL:
			InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::HandleMoveForward);
			InputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::HandleMoveRight);
			InputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerPawn::HandleSprintOn);
			InputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerPawn::HandleSprintOff);

			InputComponent->BindAction(TEXT("FlipGravity"), IE_Pressed, this, &APlayerPawn::HandleFlipGravity);
			break;
		case BARGAINING:
			InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::HandleMoveForward);
			InputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::HandleMoveRight);
			InputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerPawn::HandleSprintOn);
			InputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerPawn::HandleSprintOff);
			break;
		case OFFICE:
			break;
	}
	InputComponent->BindAction(TEXT("NextDialog"), IE_Pressed, this, &APlayerPawn::HandleDialogNext);
	InputComponent->BindAction(TEXT("PreviousDialog"), IE_Pressed, this, &APlayerPawn::HandleDialogPrev);
	
	InputComponent->BindAction(TEXT("Interact"), IE_Pressed,this, &APlayerPawn::PlayerInteract);

	InputComponent->BindAxis("RotatePickupUp", this, &APlayerPawn::HandlePickupUpRotation);
	InputComponent->BindAxis("RotatePickupRight", this, &APlayerPawn::HandlePickupRightRotation);
	
	InputComponent->BindAxis(TEXT("LookUp"), this, &APlayerPawn::HandleLookUp);
	InputComponent->BindAxis(TEXT("LookRight"), this, &APlayerPawn::HandleLookRight);

	InputComponent->BindAction(TEXT("RotateCubeUp"), IE_Pressed, this, &APlayerPawn::HandleRotateCubeUp);
	InputComponent->BindAction(TEXT("RotateCubeDown"), IE_Pressed, this, &APlayerPawn::HandleRotateCubeDown);
	InputComponent->BindAction(TEXT("RotateCubeLeft"), IE_Pressed, this, &APlayerPawn::HandleRotateCubeLeft);
	InputComponent->BindAction(TEXT("RotateCubeRight"), IE_Pressed, this, &APlayerPawn::HandleRotateCubeRight);
}

void APlayerPawn::ClearInputBindings()
{
	InputComponent->ClearActionBindings();
	InputComponent->AxisBindings.Empty();
	InputComponent->ClearBindingValues();
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	CameraHeight = Camera->GetRelativeLocation().Z;
	UE_LOG(LogTemp, Log, TEXT("CameraHaeigh shoud be %f is %f"), Camera->GetRelativeLocation().Z, CameraHeight);
	SetupInputForLevel(CurrentState);
}

void APlayerPawn::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void APlayerPawn::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	/*ADreamChaser* dreamChaser = Cast<ADreamChaser>(OtherActor);
	if(dreamChaser != nullptr)
	{
		
	}*/
}

void APlayerPawn::HandleMoveForward(float value)
{

	if(IsGravityReversed && IsCameraGravityFlip)
	{
		MovementComponent->MovementInput.X = -value;
	}
	else
	{
		MovementComponent->MovementInput.X = value;		
	}
}

void APlayerPawn::HandleMoveRight(float value)
{
	MovementComponent->MovementInput.Y = value;
}

void APlayerPawn::HandleLookUp(float value)
{
	LookingComponent->LookingInput.Y = value;
}

void APlayerPawn::HandleLookRight(float value)
{
	LookingComponent->LookingInput.X = IsGravityReversed ? -value : value;
}

void APlayerPawn::HandleSprintOn()
{
	MovementComponent->StartSprinting();
}

void APlayerPawn::HandleSprintOff()
{
	MovementComponent->StopSprinting();
}

void APlayerPawn::HandleFlipGravity()
{
	GravityFlipComponent->FlipGravity();
}

void APlayerPawn::HandleRotateCubeUp()
{
	InteractionComponent->RotateCubeUp();
}

void APlayerPawn::HandleRotateCubeDown()
{
	InteractionComponent->RotateCubeDown();
}

void APlayerPawn::HandleRotateCubeLeft()
{
	InteractionComponent->RotateCubeLeft();
}

void APlayerPawn::HandleRotateCubeRight()
{
	InteractionComponent->RotateCubeRight();
}

void APlayerPawn::HandlePickupRightRotation(float value)
{
	InteractionComponent->RotationInput.X = value;
}

void APlayerPawn::HandlePickupUpRotation(float value)
{
	InteractionComponent->RotationInput.Y = value;
}

void APlayerPawn::HandleDialogNext()
{
	DialogNextInput.Broadcast();
}

void APlayerPawn::HandleDialogPrev()
{
	DialogPrevInput.Broadcast();
}

void APlayerPawn::PlayerInteract()
{
	InteractionComponent->Interact();
}

void APlayerPawn::ToggleMovement(bool Activate)
{
	MovementComponent->bShouldMove = Activate;
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		if(IsCameraGravityFlip && bCanGravityReverse)
    	{
    		MovementComponent->GravityDirection = FVector(0, 0,
    			-FVector::DotProduct(Camera->GetUpVector(), FVector::UpVector));

			FVector CameraPos = Camera->GetRelativeLocation();
			if(MovementComponent->GravityDirection.Z > 0)
			{
				IsGravityReversed = true;
				
				
				if(CameraHeightLerpStep >= 1)
				{
					CameraHeightLerpStep = 1;
					CameraPos.Z = -CameraHeight;
				}
				else
				{
					CameraHeightLerpStep += DeltaTime;

					CameraPos.Z = FMath::Lerp(CameraHeight, -CameraHeight, CameraHeightLerpStep);
				}
			}
			else
			{
				IsGravityReversed = false;

				
				if(CameraHeightLerpStep <= 0)
				{
					CameraHeightLerpStep = 0;
					CameraPos.Z = CameraHeight;
				}
				else
				{
					CameraHeightLerpStep -= DeltaTime;
					CameraPos.Z = FMath::Lerp(CameraHeight, -CameraHeight, CameraHeightLerpStep);
				}
			}
			Camera->SetRelativeLocation(CameraPos);
        }

}

void APlayerPawn::RestartLevelOnDeath()
{
	Cast<APlayerController>(GetController())->RestartLevel();
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::DestroyPlayerInputComponent()
{
	Super::DestroyPlayerInputComponent();
}
