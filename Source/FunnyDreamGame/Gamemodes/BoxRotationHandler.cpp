#include "BoxRotationHandler.h"

UBoxRotationHandler::UBoxRotationHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBoxRotationHandler::RegisterCube(AFGRotatingLevelCube* CubeToRegister, int CubeNumber)
{
	RotationCubes.Emplace(CubeNumber, CubeToRegister);
}

void UBoxRotationHandler::RegisterRotatorCube(ARotatorCube* CubeToRegister, int CubeNumber)
{
	RotationCubes[CubeNumber]->RegisterRotatorCube(CubeToRegister);
}

AFGRotatingLevelCube* UBoxRotationHandler::GetCube(int CubeNumber)
{
	return RotationCubes[CubeNumber];
}

TArray<ARotatorCube*> UBoxRotationHandler::GetRotatorCubes(int CubeNumber)
{
	return RotationCubes[CubeNumber]->GetRotatorCubes();
}



