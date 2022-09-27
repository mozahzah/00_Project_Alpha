// Fill out your copyright notice in the Description page of Project Settings.


#include "PreSmokeActor.h"


// Sets default values
APreSmokeActor::APreSmokeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APreSmokeActor::BeginPlay()
{
	Super::BeginPlay();
	//PreSmokeParticle->Activate();
	
}

// Called every frame
void APreSmokeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

