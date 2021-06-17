// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GravityZone.generated.h"

class AFGSplineActor;

UCLASS()
class FUNNYDREAMGAME_API AGravityZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	APawn* Player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartUsingGravityZone();
	UFUNCTION(BlueprintCallable)
	void StopUsingGravityZone();
	

	UPROPERTY(EditAnywhere)
	AFGSplineActor* GravitySpline;

	bool bUseGravityZone = false;

	FVector GravityDirection;
};
