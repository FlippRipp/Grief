// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityZone.h"
#include "FGSplineActor.h"
#include "Components/SplineComponent.h"
#include "FunnyDreamGame/Player/PlayerPawn.h"

// Sets default values
AGravityZone::AGravityZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGravityZone::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<APlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void AGravityZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bUseGravityZone || Player == nullptr) return;

	FRotator closestSplineRotation = GravitySpline->Spline->FindRotationClosestToWorldLocation(GetActorLocation(),
 	ESplineCoordinateSpace::World);
	
	
}

void AGravityZone::StartUsingGravityZone()
{
	bUseGravityZone = true;
}

void AGravityZone::StopUsingGravityZone()
{
	bUseGravityZone = false;

}

