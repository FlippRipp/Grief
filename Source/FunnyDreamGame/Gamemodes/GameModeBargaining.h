#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBargaining.generated.h"

class UFGRotatingLevelCube;

UCLASS()
class FUNNYDREAMGAME_API AGameModeBargaining : public AGameModeBase
{
	GENERATED_BODY()

	//Methods:
public:

protected:

	//Variables:
public:
	UFGRotatingLevelCube* LevelCube;
protected:
};
