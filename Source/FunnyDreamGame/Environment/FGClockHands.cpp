// Fill out your copyright notice in the Description page of Project Settings.


#include "FGClockHands.h"
#include "FunnyDreamGame/Gamemodes/WallDestructionHandler.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
AFGClockHands::AFGClockHands()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called when the game starts or when spawned
void AFGClockHands::BeginPlay()
{
	Super::BeginPlay();
	auto actorComponent = UGameplayStatics::GetGameMode(this)->GetComponentByClass(UWallDestructionHandler::StaticClass());
	if (actorComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Emrik fucked up"));
	}
	auto wallDestructionHandler = Cast<UWallDestructionHandler>(actorComponent);
	if (wallDestructionHandler != nullptr)
	{
		wallDestructionHandler->RegisterClockHands(this);
	}
}

// Called every frame
void AFGClockHands::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

