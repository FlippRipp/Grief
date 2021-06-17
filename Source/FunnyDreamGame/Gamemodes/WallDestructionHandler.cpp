// Fill out your copyright notice in the Description page of Project Settings.


#include "WallDestructionHandler.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "FunnyDreamGame/Environment/FGClockHands.h"



UWallDestructionHandler::UWallDestructionHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWallDestructionHandler::ReportDestroyedWall()
{
	ClockHands->MoveDemHands();
	DestructionCountLeft--;
	if(DestructionCountLeft <= 0)
	{
		/*auto gameMode = UGameplayStatics::GetGameMode(this);
		gameMode->ResetLevel();*/
		/*ClockHands->MoveDemHands();
		auto playerController = UGameplayStatics::GetGameInstance(this)->GetPrimaryPlayerController();
		playerController->RestartLevel();*/
		//gameMode->RestartPlayer(playerController);
		
	}
}

void UWallDestructionHandler::RegisterClockHands(AFGClockHands* clockhands)
{
	ClockHands = clockhands;
}

void UWallDestructionHandler::AddDestructionCount(int AttemptsToAdd)
{
	DestructionCountLeft += AttemptsToAdd;
}


void UWallDestructionHandler::BeginPlay()
{
	Super::BeginPlay();

	DestructionCountLeft = StartWallDestructionCount;
}

