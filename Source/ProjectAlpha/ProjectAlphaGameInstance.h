// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Crossair.h"
#include "Engine/GameInstance.h"
#include "ProjectAlphaGameInstance.generated.h"



class UUserWidget;
/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UProjectAlphaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	virtual void Init() override;
	TSubclassOf<UUserWidget> CrossairClass;

	
	
public:
	
	UProjectAlphaGameInstance(const FObjectInitializer & ObjectInitializer);
	

	UFUNCTION(BlueprintCallable)
	void AddReticle();

	//bool InitSoundEngine();

};
