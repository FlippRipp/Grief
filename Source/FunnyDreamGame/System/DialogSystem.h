// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "FunnyDreamGame/DialogSequence.h"
#include "GameFramework/Actor.h"
#include "DialogSystem.generated.h"

class UDialogSequence;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogChanged, FDialog, Dialog);

UCLASS()
class FUNNYDREAMGAME_API ADialogSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ProgressDialog();
	UFUNCTION(BlueprintCallable)
	void RegressDialog();

	UFUNCTION(BlueprintCallable)
	void UpdateDialog();

	UPROPERTY(EditAnywhere)
	UDialogSequence* Dialog;

	UPROPERTY(BlueprintAssignable)
	FDialogEnd OnDialogEnd;
	
	UPROPERTY(BlueprintAssignable)
	FDialogChanged OnDialogChanged;
	
	int CurrentDialogPhase = 0;

};
