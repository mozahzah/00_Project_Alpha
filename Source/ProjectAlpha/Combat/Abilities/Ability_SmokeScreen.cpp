// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_SmokeScreen.h"

#include "DrawDebugHelpers.h"

#include "ProjectAlpha/GamePlayActors/SmokeScreenActor.h"

void UAbility_SmokeScreen::OnInitialize()
{
	if (OwnerActor.IsValid())
	{
		if (const UWorld* World = OwnerActor->GetWorld())
		{
			MyWorld = World;
		}
	}
}

void UAbility_SmokeScreen::OnActivate(bool& bSuccess)
{
	if (OwnerActor.IsValid())
	{
		SmokeLocation = OwnerActor->GetActorLocation();

		if (MyWorld.IsValid() && OwnerActor.IsValid())
		{
			PreSmokeScreenActor = GetWorld()->SpawnActor<ASmokeScreenActor>(PreSmokeScreenActorClass, SmokeLocation, OwnerActor->GetActorRotation(), FActorSpawnParameters());
		}
		bSuccess = true;

		bAbilityIsActive = true;
	}
}

void UAbility_SmokeScreen::OnUpdate(float DeltaTime)
{
	/*if (bFireButtonIsHeld)
	{
		DistanceFromPlayer += PreSmokeSpeed * DeltaTime;
	}
	if (bSecondaryFireButtonHeld)
	{
		DistanceFromPlayer = FMath::Clamp(DistanceFromPlayer, 0.0f, DistanceFromPlayer -= PreSmokeSpeed * DeltaTime);
	}*/

	if (OwnerActor.IsValid())
	{
		SmokeLocation = OwnerActor->GetActorLocation() + OwnerActor->GetActorForwardVector() * DistanceFromPlayer;
	}

	if (bAbilityIsActive)
	{
		if (PreSmokeScreenActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *SmokeLocation.ToString());
			PreSmokeScreenActor->SetActorLocation(SmokeLocation);
		}
	}

	//if (!bSmokeHasBeenDeployed)
	//{
	//	if (PreSmokeScreenActor)
	//	{
	//		PreSmokeScreenActor->Destroy();
	//	}

	//	if (MyWorld.IsValid() && OwnerActor.IsValid())
	//	{
	//		GetWorld()->SpawnActor<ASmokeScreenActor>(SmokeScreenActorClass, SmokeLocation, OwnerActor->GetActorRotation(), FActorSpawnParameters());
	//	}

	//	bSmokeHasBeenDeployed = true;
	//}
}

void UAbility_SmokeScreen::OnDeactivate()
{
	bAbilityIsActive = false;
	DistanceFromPlayer = 0.0f;
}

void UAbility_SmokeScreen::OnFireStart()
{
	//bFireButtonIsHeld = true;
}

void UAbility_SmokeScreen::OnFireStop()
{
	//bFireButtonIsHeld = false;
}