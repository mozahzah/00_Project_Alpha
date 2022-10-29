// Fill out your copyright notice in the Description page of Project Settings.


#include "SmokeScreenActor.h"

// Sets default values
ASmokeScreenActor::ASmokeScreenActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	

}

// Called when the game starts or when spawned
void ASmokeScreenActor::BeginPlay()
{
	Super::BeginPlay();
	Timer = GetWorld()->GetTimeSeconds();
	
}

// Called every frame
void ASmokeScreenActor::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	if (GetWorld()->GetTimeSeconds() - Timer > 15)
	{
		Destroy();
	}
	
}

