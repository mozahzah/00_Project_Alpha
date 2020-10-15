// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crossair.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UCrossair : public UUserWidget
{
	GENERATED_BODY()

	bool Initialize();
	void BeginPlay();
};
