// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentActor.h"
#include "AkComponent.h"

// Sets default values
AEnvironmentActor::AEnvironmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnvironmentActor::BeginPlay()
{
	Super::BeginPlay();
	const FOnAkPostEventCallback PostEventCallback;
	const FString EventName;
	AkMainComponent = FindComponentByClass<UAkComponent>();
	auto PlayingId = AkMainComponent->PostAkEvent(LightSfxEvent, 0, PostEventCallback, EventName);
}

// Called every frame
void AEnvironmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

