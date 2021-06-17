// Fill out your copyright notice in the Description page of Project Settings.


#include "FGLevelSelector.h"

#include "Components/BoxComponent.h"


// Sets default values
AFGLevelSelector::AFGLevelSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
}

void AFGLevelSelector::ChangeLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), NewLevel);
}

// Called when the game starts or when spawned
void AFGLevelSelector::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFGLevelSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

