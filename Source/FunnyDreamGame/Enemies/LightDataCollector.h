#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LightDataCollector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNYDREAMGAME_API ULightDataCollector : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULightDataCollector();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	UMaterialParameterCollection* LightMaterialCollection;

	UPROPERTY(EditAnywhere)
	float CollectionRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> PointLightOverlapObjectTypes;
	protected:
	
};
