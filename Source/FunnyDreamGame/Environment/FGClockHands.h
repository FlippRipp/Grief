// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGClockHands.generated.h"

UCLASS()
class FUNNYDREAMGAME_API AFGClockHands : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGClockHands();
	UFUNCTION(BlueprintImplementableEvent, Category = "Lol")
	void MoveDemHands();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
