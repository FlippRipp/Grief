// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogSystem.h"


#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

//#include "FunnyDreamGame/DialogSequence.h"

// Sets default values
ADialogSystem::ADialogSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADialogSystem::BeginPlay()
{
	Super::BeginPlay();
	OnDialogChanged.Broadcast(Dialog->Dialogs[CurrentDialogPhase]);	
}

// Called every frame
void ADialogSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADialogSystem::ProgressDialog()
{	
	if(CurrentDialogPhase + 1 >= Dialog->Dialogs.Num())
	{
		OnDialogEnd.Broadcast();
		UE_LOG(LogTemp, Log, TEXT("Can't Next Dialog"))
	}
	else
	{
		CurrentDialogPhase++;
		UpdateDialog();
		UE_LOG(LogTemp, Log, TEXT("Next Dialog"))
	}
}

void ADialogSystem::RegressDialog()
{

	if(CurrentDialogPhase <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Can't Prev Dialog"))
	}
	else
	{
		CurrentDialogPhase--;
		UpdateDialog();
		UE_LOG(LogTemp, Log, TEXT("Prev Dialog"))
	}

}

void ADialogSystem::UpdateDialog()
{
	OnDialogChanged.Broadcast(Dialog->Dialogs[CurrentDialogPhase]);
	
}
