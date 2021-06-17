#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FunnyDreamGame/Environment/FGRotatingLevelCube.h"
#include "FunnyDreamGame/Environment/RotatorCube.h"

#include "BoxRotationHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNYDREAMGAME_API UBoxRotationHandler : public UActorComponent
{
	GENERATED_BODY()

	//Methods:
public:	
	UBoxRotationHandler();

	void RegisterCube(AFGRotatingLevelCube* CubeToRegister, int CubeNumber);
	void RegisterRotatorCube(ARotatorCube* CubeToRegister, int CubeNumber);
	AFGRotatingLevelCube* GetCube(int CubeNumber);
	TArray<ARotatorCube*> GetRotatorCubes(int CubeNumber);
protected:
	
	//Variables:
public:	
protected:
	UPROPERTY()
	TMap<int, AFGRotatingLevelCube*> RotationCubes;
	UPROPERTY()
	ARotatorCube* RotatorCube;
	UPROPERTY()
	ARotatorCube* OtherRotatorCube;

};
