// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PreSmokeActor.generated.h"


UCLASS()
class PROJECTALPHA_API APreSmokeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreSmokeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UParticleSystemComponent* PreSmokeParticle;
		
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
