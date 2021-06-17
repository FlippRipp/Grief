#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGLookingComponent.generated.h"

class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNYDREAMGAME_API UFGLookingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFGLookingComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FVector2D LookingInput;

	void SetCamera(UCameraComponent* pCamera);

	UPROPERTY(EditAnywhere)
	bool bPitchIsClamped = false;
	UPROPERTY(EditAnywhere)
	bool bYawIsClamped = false;

	UPROPERTY(EditAnywhere)
	float PitchMax = 80.0f;
	UPROPERTY(EditAnywhere)
	float YawMax = 80.0f;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float YawSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
	float PitchSpeed = 100.0f;

	void LookUp(float DeltaTime);
	void LookRight(float DeltaTime);
private:
	UCameraComponent* LookingCamera;
};
