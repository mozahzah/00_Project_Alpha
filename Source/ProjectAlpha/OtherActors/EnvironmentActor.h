// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentActor.generated.h"

UCLASS()
class PROJECTALPHA_API AEnvironmentActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnvironmentActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UAkComponent* AkMainComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "Wwise")
	class UAkAudioEvent* LightSfxEvent = nullptr;



};
