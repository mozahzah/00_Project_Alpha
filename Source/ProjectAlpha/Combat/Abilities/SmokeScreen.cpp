// Fill out your copyright notice in the Description page of Project Settings.


#include "SmokeScreen.h"
#include "ProjectAlpha/OtherActors/SmokeScreenActor.h"

// Sets default values for this component's properties
USmokeScreen::USmokeScreen()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USmokeScreen::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}


// Called every frame
void USmokeScreen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (bSmokeIsActive) 
	{
		SetSmokeLocation(SmokeScreenActor);	
	}
	

	// ...
}

void USmokeScreen::SetSmokeLocation(ASmokeScreenActor* SmokeActor) 
{
	auto ActorLocation = GetOwner()->GetActorLocation();
	if (FVector::Distance(ActorLocation, CurrentLocation) >= FVector::Distance(ActorLocation, EndLocation))
	{
		bSmokeIsActive = false;
	}
	else 
	{
		CurrentLocation += ForwardVector * 10;
		SmokeActor->SetActorLocation(CurrentLocation);
	}
}

void USmokeScreen::ActivateSmokeScreen(FVector SmokeLocationToSet)
{
	CurrentLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100;
	ForwardVector = GetOwner()->GetActorForwardVector();
	FActorSpawnParameters SpawnParameters;
	SmokeScreenActor = GetWorld()->SpawnActor<ASmokeScreenActor>(SmokeBlueprint, CurrentLocation, GetOwner()->GetActorRotation(), SpawnParameters);
	EndLocation = SmokeLocationToSet;
	bSmokeIsActive = true;
	
}

void USmokeScreen::DeactivateSmokeScreen()
{
	
}

