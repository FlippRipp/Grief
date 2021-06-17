// Fill out your copyright notice in the Description page of Project Settings.


#include "FGSplineActor.h"
#include "Components/SplineComponent.h"

// Sets default values
AFGSplineActor::AFGSplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));

}

// Called when the game starts or when spawned
void AFGSplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFGSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USplineComponent* AFGSplineActor::GetSplineComponent()
{
	return Spline;
}

