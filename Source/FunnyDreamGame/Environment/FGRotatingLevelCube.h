#pragma once

#include "CoreMinimal.h"

#include "RotatorCube.h"
#include "GameFramework/Actor.h"
#include "FGRotatingLevelCube.generated.h"

UCLASS()
class FUNNYDREAMGAME_API AFGRotatingLevelCube : public AActor
{
	GENERATED_BODY()

	//Methods:
public:	
	AFGRotatingLevelCube();
	void QueueRotation(FRotator Rotation);
	void RegisterRotatorCube(ARotatorCube* Caller);
	TArray<ARotatorCube*> GetRotatorCubes();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void RotateCube(float DeltaSeconds);
	
	//Variables:
public:	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxPivot;

	UPROPERTY(EditAnywhere)
	int BoxNumber = 1;

	UFUNCTION(BlueprintImplementableEvent)
	void OnCubeRotation();

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 2.0f;;
protected:	
	FRotator GoalRotation;
	float RotationFraction =0.0f;
	TArray<FQuat> RotationQueue;

	UPROPERTY()
	TArray<ARotatorCube*> RotatorCubes;
};
