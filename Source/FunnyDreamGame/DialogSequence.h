// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "DialogSequence.generated.h"

USTRUCT(BluePrintable)
struct FDialog{
 
    GENERATED_USTRUCT_BODY()

 
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString DialogText;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* CharacterImage;
};

UCLASS()
class FUNNYDREAMGAME_API UDialogSequence : public UDataAsset
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere)
	TArray<FDialog> Dialogs;
};
