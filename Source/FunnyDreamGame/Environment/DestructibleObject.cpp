// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleObject.h"

#include "FunnyDreamGame/Gamemodes/WallDestructionHandler.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

ADestructibleObject::ADestructibleObject() : Super()
{
	
}

void ADestructibleObject::Interact(UFGInteractionComponent* Interacter)
{
	// FVector* actorLocation = GetActorLocation();
	// GetWorld()->SpawnActor(ExplodingMeshActor, GetActorLocation(), GetActorRotation());
	// Mesh->SetActive(false);

	OnObjectDestroyed.Broadcast();

	if(bShouldReportWall)
	{
		auto actorComponent = UGameplayStatics::GetGameMode(this)->GetComponentByClass(UWallDestructionHandler::StaticClass());
		if(actorComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Please attach a WallDestructionHandler component to the GameMode used where you want to destroy walls (or talk to Fredrik :))"));
		}
		auto wallDestructionHandler = Cast<UWallDestructionHandler>(actorComponent);
		if(wallDestructionHandler != nullptr)
		{
			wallDestructionHandler->ReportDestroyedWall();
		}	
	}
	Destroy();
}