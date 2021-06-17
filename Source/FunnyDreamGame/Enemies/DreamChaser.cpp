#include "DreamChaser.h"
#include "Components/CapsuleComponent.h"
#include "Components/LightComponent.h"
#include "Components/SplineComponent.h"
#include "Engine/Light.h"
#include "Engine/SpotLight.h"
#include "FunnyDreamGame/Environment/FGSplineActor.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceConstant.h"

ADreamChaser::ADreamChaser()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
}

void ADreamChaser::BeginPlay()
{
	Super::BeginPlay();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ADreamChaser::OnBeginOverlap);
}
// FVector ClosestSplinePoint = Spline->FindLocationClosestToWorldLocation(player->GetActorLocation(),
// 	ESplineCoordinateSpace::World);

void ADreamChaser::ChasePlayer(float DeltaTime)
{
	APawn* player = GetWorld()->GetFirstPlayerController()->GetPawn();


	if(player == nullptr || SplineActor == nullptr)
		return;

	USplineComponent* Spline = SplineActor->GetSplineComponent();

	if(SplineStep < 1)
	{
		SplineStep += (MovementSpeed * DeltaTime * GetPlayerDistanceMultiplier()) / Spline->GetSplineLength();
		if(SplineStep > 1)
		{
			SplineStep = 1;
		}
	}

	// FVector DirToMoveIn = (Spline->GetLocationAtTime(SplineStep, ESplineCoordinateSpace::World)
	// 	- GetActorLocation()).GetSafeNormal();
	//
	//
	// FVector moveDelta =  DirToMoveIn * MovementSpeed * DeltaTime;

	SetActorLocation(Spline->GetLocationAtTime(SplineStep, ESplineCoordinateSpace::World, true));
	
	//AddActorWorldOffset(moveDelta, true);
}

float ADreamChaser::GetPlayerDistanceMultiplier()
{
	FVector playerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	float distanceToPlayer = FVector::Distance(GetActorLocation(), playerLocation);
	float speedMultiplier = SpeedToPlayerDistance->GetFloatValue(distanceToPlayer/SpeedMultiplierPlayerMaxDistance);
	return speedMultiplier;
}

void ADreamChaser::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                  int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	CheckOverlapWithLights(OtherActor);
	CheckOverlapWithStaticMesh(OtherComp);
}

void ADreamChaser::FlickerLights(float DeltaTime)
{
	// TArray<int> indiciesToRemove;
	for(int i = FlickeringLights.Num() - 1; i >= 0; i--)
	{
		FlickeringLight& light = FlickeringLights[i];

		light.LightFlickerTime += DeltaTime;
		float t = light.LightFlickerTime / LightFlickerDuration;
		float lightCurveMultiplier = LightFlickeringCurve->GetFloatValue(t);
		light.Light->SetIntensity(light.StartIntensity * lightCurveMultiplier);
		if(t >= 1)
		{
			OnLightBreaking.Broadcast(light.Light->GetComponentLocation());
			FlickeringLights.RemoveAt(i);
		}
	}

	// for(auto i : indiciesToRemove)
	// {
	// 	// FlickeringLights[i]->Light->DestroyComponent();
	// 	FlickeringLights.RemoveAt(i);
	// }
}

void ADreamChaser::FlickerMeshes(float DeltaTime)
{
	for(int i = FlickeringMeshes.Num() - 1; i >= 0; i--)
	{
		FlickeringMesh& mesh = FlickeringMeshes[i];

		mesh.LightFlickerTime += DeltaTime;
		float t = mesh.LightFlickerTime / LightFlickerDuration;
		float lightCurveMultiplier = LightFlickeringCurve->GetFloatValue(t);
		mesh.MaterialInstance->SetScalarParameterValue("EmmisiveIntensity", mesh.StartIntensity * lightCurveMultiplier);
		if(t >= 1)
		{
			FlickeringMeshes.RemoveAt(i);
		}
	}
}

void ADreamChaser::CheckOverlapWithLights(AActor* OtherActor)
{
	ASpotLight* lightActor = Cast<ASpotLight>(OtherActor);
	if(lightActor == nullptr)
		return;
	
	ULightComponent* light = lightActor->GetLightComponent();
	
	if(light == nullptr)
		return;
	
	FlickeringLight newLight;
	newLight.Light = light;
	newLight.LightFlickerTime = 0;
	newLight.StartIntensity = light->Intensity;
	FlickeringLights.Add(newLight);

	OnLightFlickerStart.Broadcast(lightActor->GetActorLocation());
}

void ADreamChaser::CheckOverlapWithStaticMesh(UPrimitiveComponent* OtherComp)
{
	UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(OtherComp);
	
	if(meshComponent == nullptr)
		return;

	if(!meshComponent->ComponentHasTag("CorridorLightMesh"))
		return;
	
	FlickeringMesh newFlickeringMesh;
	UMaterialInstance* meshMat = Cast<UMaterialInstance>(meshComponent->GetMaterial(0));
	if(!meshMat)
		return;
	
	UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(meshMat, meshComponent->GetOuter());
	meshComponent->SetMaterial(0, dynamicMaterial);
	newFlickeringMesh.StartIntensity = 0.3f;
	newFlickeringMesh.LightFlickerTime = 0;
	newFlickeringMesh.MaterialInstance = dynamicMaterial;
	
	FlickeringMeshes.Add(newFlickeringMesh);
}

void ADreamChaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bShouldMove)
	{
		ChasePlayer(DeltaTime);
	}

	if(FlickeringLights.Num() > 0)
	{
		FlickerLights(DeltaTime);
	}

	if(FlickeringMeshes.Num() > 0)
	{
		FlickerMeshes(DeltaTime);
	}
}




// float PlayerSplineTime = Spline->FindInputKeyClosestToWorldLocation(player->GetActorLocation())
//     / Spline->GetNumberOfSplinePoints();
//
// FVector DirToMoveIn = FVector::ZeroVector;
//
// 	
// if(FVector::Distance(GetActorLocation(), Spline->GetLocationAtTime(PlayerSplineTime, ESplineCoordinateSpace::World,
//     true)) > 0)
// {
// 	float EnemySplineTime = Spline->FindInputKeyClosestToWorldLocation(GetActorLocation())
//     / Spline->GetNumberOfSplinePoints();
//
// 	float TimeDir = FMath::Sign(PlayerSplineTime - EnemySplineTime);
// 	DirToMoveIn = (Spline->GetLocationAtTime(EnemySplineTime + TimeDir * 0.001f, ESplineCoordinateSpace::World)
//         - GetActorLocation()).GetSafeNormal();
// 		
// }
//
// 	
// FVector dirToPlayer = player->GetActorLocation() - GetActorLocation();
// // FVector dirToSplinePoint = (ClosestSplinePoint - GetActorLocation()).GetSafeNormal();
// // dirToPlayer.Z = 0;
// FRotator rotToPlayer = dirToPlayer.Rotation();
// SetActorRotation(rotToPlayer);
//
// FVector moveDelta =  DirToMoveIn * MovementSpeed * DeltaTime;
//
//
