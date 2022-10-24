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
		bSuccess = true;
	}
}

void UAbility_SmokeScreen::OnUpdate(float DeltaTime)
{

	if (bFireButtonIsHeld)
	{
		DistanceFromPlayer += bDeployementSpeed * DeltaTime;
	}
	if (bSecondaryFireButtonHeld)
	{
		DistanceFromPlayer = FMath::Clamp(DistanceFromPlayer, 0.0f, DistanceFromPlayer -= bDeployementSpeed * DeltaTime);
	}

	if (OwnerActor.IsValid())
	{
		SmokeLocation = OwnerActor->GetActorLocation() + OwnerActor->GetActorForwardVector() * DistanceFromPlayer;
	}

	if (bAbilityIsActive)
	{
		if (MyWorld.IsValid())
		{
			DrawDebugCircle(MyWorld.Get(), SmokeLocation, PreSmokeWidgetSize, 6, FColor::Cyan);
		}
	}

	if (bSmokeHasBeenDeployed)
	{
		// DEPLY ACTOR
	}
}

void UAbility_SmokeScreen::OnDeactivate()
{
	bAbilityIsActive = false;
	if (MyWorld.IsValid() && OwnerActor.IsValid())
	{
		GetWorld()->SpawnActor<ASmokeScreenActor>(SmokeScreenActor, SmokeLocation, OwnerActor->GetActorRotation(), FActorSpawnParameters());
	}
	DistanceFromPlayer = 0.0f;
}

void UAbility_SmokeScreen::OnFireStart()
{
	//bAbilityIsActive = false;
}