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
	
}

// Called every frame
void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	SetActorLocation(GetActorLocation() + FVector(0, 0, 0.4) * FMath::Sin(GetWorld()->GetRealTimeSeconds() *2.5));


}

