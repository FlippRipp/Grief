// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "DreamChaser.generated.h"

class USphereComponent;
class UCapsuleComponent;
class ULightComponent;
class AFGSplineActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLightBreakingDelegate, FVector, LightPosition);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLightOverLapDelegate);

USTRUCT()
struct FlickeringLight
{
	GENERATED_BODY()

	UPROPERTY()
	ULightComponent* Light;
	float LightFlickerTime = 0.0f;
	float StartIntensity = 0.0f;
};

USTRUCT()
struct FlickeringMesh
{
	GENERATED_BODY()

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance;

	float LightFlickerTime = 0.0f;
	float StartIntensity = 0.0f;
};

UCLASS()
class FUNNYDREAMGAME_API ADreamChaser : public APawn
{
	GENERATED_BODY()

public:
	ADreamChaser();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 50.0f;

	float SplineStep = 0;

	void ChasePlayer(float DeltaTime);

	float GetPlayerDistanceMultiplier();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);

	void FlickerLights(float DeltaTime);
	void FlickerMeshes(float DeltaTime);

	void CheckOverlapWithLights(AActor* OtherActor);
	void CheckOverlapWithStaticMesh(UPrimitiveComponent* OtherComp);	
public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AFGSplineActor* SplineActor;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldMove = false;

	UPROPERTY(BlueprintAssignable)
	FLightBreakingDelegate OnLightFlickerStart;

	UPROPERTY(BlueprintAssignable)
	FLightBreakingDelegate OnLightBreaking;

	UPROPERTY(EditAnywhere)
	UCurveFloat* SpeedToPlayerDistance;

	UPROPERTY(EditAnywhere)
	UCurveFloat* LightFlickeringCurve;

	UPROPERTY(EditAnywhere)
	float LightFlickerDuration = 1.0f;
	
	UPROPERTY(EditAnywhere)
	float SpeedMultiplierPlayerMaxDistance = 2000.0f;

private:

	UPROPERTY()
	TArray<FlickeringLight>FlickeringLights;

	UPROPERTY()
	TArray<FlickeringMesh> FlickeringMeshes;
};
