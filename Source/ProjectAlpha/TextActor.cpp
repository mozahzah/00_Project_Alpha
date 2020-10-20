// Fill out your copyright notice in the Description page of Project Settings.


#include "TextActor.h"

// Sets default values
ATextActor::ATextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATextActor::BeginPlay()
{
	Super::BeginPlay();
	Height = FMath::RandRange(0.1f, 0.4f);
	Speed = FMath::RandRange(2, 3);
}

// Called every frame
void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bisFloating)
	{
		;
		SetActorLocation(GetActorLocation() + FVector(0, 0, Height) * FMath::Sin(GetWorld()->GetRealTimeSeconds() *Speed));
	}


}

