// Fill out your copyright notice in the Description page of Project Settings.


#include "LightDataCollector.h"

#include "Components/PointLightComponent.h"
#include "Engine/PointLight.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"

ULightDataCollector::ULightDataCollector()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULightDataCollector::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULightDataCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// TArray<UPrimitiveComponent*> overlappedComponents;
	// if(!UKismetSystemLibrary::SphereOverlapComponents(this,
	// 	GetOwner()->GetActorLocation(),
	// 	CollectionRange,
	// 	PointLightOverlapObjectTypes,
	// 	UPointLightComponent::StaticClass(),
	// 	TArray<AActor*>(),
	// 	overlappedComponents))
	// return; //Nothing was found

	TArray<AActor*> overlappedLights;
	if(!UKismetSystemLibrary::SphereOverlapActors(this,
		GetOwner()->GetActorLocation(),
		CollectionRange,
		PointLightOverlapObjectTypes,
		APointLight::StaticClass(),
		TArray<AActor*>(),
		overlappedLights))
			return; //Nothing was found

	
	FVector currentPos = GetOwner()->GetActorLocation();
	overlappedLights.Sort([currentPos] (const AActor& LHS, const AActor& RHS)
	{
		const float lhsDistance = FVector::DistSquared(currentPos, LHS.GetActorLocation());
		const float rhsDistance = FVector::DistSquared(currentPos, RHS.GetActorLocation());
	
		return lhsDistance > rhsDistance;
	});
	
	UMaterialParameterCollectionInstance* instance;
	instance = GetWorld()->GetParameterCollectionInstance(LightMaterialCollection);
	UPointLightComponent* lightOne = Cast<UPointLightComponent>(overlappedLights[0]->GetComponentByClass(UPointLightComponent::StaticClass()));
	
	instance->SetScalarParameterValue("Light1Intensity", lightOne->Intensity);
	instance->SetScalarParameterValue("Light1Attenuation", lightOne->AttenuationRadius);
	
	FVector lightOneDir = lightOne->GetOwner()->GetActorLocation() - currentPos;
	lightOneDir = lightOneDir.GetSafeNormal(0.1f);
	
	instance->SetVectorParameterValue("Light1Vector", lightOneDir);
	instance->SetVectorParameterValue("Light1Color", lightOne->LightColor);
	
	if(overlappedLights.Num() < 2)
		return;
	
	UPointLightComponent* lightTwo = Cast<UPointLightComponent>(overlappedLights[1]->GetComponentByClass(UPointLightComponent::StaticClass()));
	
	instance->SetScalarParameterValue("Light2Intensity", lightTwo->Intensity);
	instance->SetScalarParameterValue("Light2Attenuation", lightTwo->AttenuationRadius);
	
	FVector lightTwoDir = lightTwo->GetOwner()->GetActorLocation() - currentPos;
	lightTwoDir = lightTwoDir.GetSafeNormal(0.1f);
	
	instance->SetVectorParameterValue("Light2Vector", lightTwoDir);
	instance->SetVectorParameterValue("Light2Color", lightTwo->LightColor);
}

