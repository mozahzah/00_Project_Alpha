// Fill out your copyright notice in the Description page of Project Settings.


#include "OcclusionManager.h"
#include "AkComponent.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>

// Sets default values for this component's properties
UOcclusionManager::UOcclusionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOcclusionManager::BeginPlay()
{
	Super::BeginPlay();

	// Get Surface Type
	

	
	
	
}


// Called every frame
void UOcclusionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//AkReal32 fObstruction = 0;
	//AkReal32 fOcclusion = 0.5;
	//AkGameObjectID in_EmitterID = 0;
	//AkGameObjectID in_ListenerID = 0;

	//for (int iGameObject = 0; iGameObject < 3; iGameObject++) 
	//{



	//}

	//auto Success = AK::SoundEngine::SetObjectObstructionAndOcclusion(in_EmitterID, in_ListenerID, fObstruction, fOcclusion);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), GetWorld()->);
}

