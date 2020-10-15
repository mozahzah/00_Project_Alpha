// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoverSpotActor.generated.h"

UCLASS()
class PROJECTALPHA_API ACoverSpotActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoverSpotActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
