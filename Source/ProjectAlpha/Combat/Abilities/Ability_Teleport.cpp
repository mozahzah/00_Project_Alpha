// Copyright 2023 mozahzah. All Rights Reserved.

#include "Ability_Teleport.h"

#include "DrawDebugHelpers.h"

void UAbility_Teleport::OnActivate(bool& bSuccess)
{
	bSuccess = true;
}

void UAbility_Teleport::OnUpdate(float DeltaTime)
{
	ProcessLineTrace();

	if (bIsTeleporting) 
	{
		if (Timer > TeleportTime)
		{
			Teleport();
		}

		Timer += DeltaTime;
	}
}

void UAbility_Teleport::OnDeactivate()
{
	bIsLocked = false;
	bIsTeleporting = false;
	Timer = 0.0f;
}

void UAbility_Teleport::OnFireStart()
{
	bIsLocked = true;
	bIsTeleporting = true;
	if (OwnerActor.IsValid())
	{
		OwnerActor->DisableInput(Cast<APlayerController>(OwnerController.Get()));
	}
}

void UAbility_Teleport::ProcessLineTrace()
{
	//Line trace 1
	if (OwnerController.IsValid())
	{
		if (const UWorld* const World = OwnerController->GetWorld())
		{
			FVector ViewpointLocation;
			FRotator ViewpointRotation;
			OwnerController->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);

			FVector Start = ViewpointLocation;
			FVector End = ViewpointLocation + ViewpointRotation.Vector() * TeleportMaxLineTrace;

			FHitResult HitResult;
			if (World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility))
			{
				CurrentTeleportLocation = HitResult.Location;
			}
			else
			{
				//Line trace 2
				if (World->LineTraceSingleByChannel(HitResult, End, End.DownVector * MAX_FLT, ECollisionChannel::ECC_Visibility))
				{
					CurrentTeleportLocation = HitResult.Location;
				}
			}

			DrawDebugSphere(World, CurrentTeleportLocation, 8.f, 8, FColor::Blue, false, 0.1f, 10, 1.0f);
		}
	}
}

void UAbility_Teleport::Teleport()
{
	if (OwnerActor.Get()) 
	{
		OwnerActor->SetActorLocation(CurrentTeleportLocation);
		OwnerActor->EnableInput(Cast<APlayerController>(OwnerController.Get()));
	}
	Deactivate();
}