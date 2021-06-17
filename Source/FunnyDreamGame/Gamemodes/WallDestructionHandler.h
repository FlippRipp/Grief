// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallDestructionHandler.generated.h"
class AFGClockHands;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNYDREAMGAME_API UWallDestructionHandler : public UActorComponent
{
	GENERATED_BODY()

	//Methods:
public:	
	UWallDestructionHandler();
	void ReportDestroyedWall();

	void RegisterClockHands(AFGClockHands* clockhands);

	UFUNCTION(BlueprintCallable)
	void AddDestructionCount(int AttemptsToAdd);
protected:
	void BeginPlay() override;

	//Variables:
public:	
	UPROPERTY(EditAnywhere)
	int StartWallDestructionCount = 6;

	UPROPERTY()
	AFGClockHands* ClockHands;
protected:
	int DestructionCountLeft;
};
