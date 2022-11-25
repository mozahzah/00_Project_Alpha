// Copyright 2023 mozahzah. All Rights Reserved.

#include "Ability_Telekinesis.h"

#include "Particles/ParticleSystemComponent.h"

#include "ProjectAlpha/GamePlayActors/LevitatingActor.h"

void UAbility_Telekinesis::OnActivate(bool& bSuccess)
{
	if (RayCastObjects()) 
	{
		bSuccess = true;
	}
}

void UAbility_Telekinesis::OnDeactivate()
{
	ReleaseObjects();
	bAbilityIsActive = false;
}

void UAbility_Telekinesis::OnFireStart()
{
	if (OwnerController.IsValid()) 
	{
		FVector ViewpointLocation;
		FRotator ViewpointRotation;
		OwnerController->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);

		if (!LevitatingActors.IsEmpty())
		{
			if (TObjectPtr<ALevitatingActor> LevitatingActor = LevitatingActors.Pop())
			{
				LevitatingActor->RequestFire(ViewpointRotation.Vector());

				/* When the last object is popped we deactivate the ability */
				if (LevitatingActors.IsEmpty())
				{
					Deactivate();
				}
			}
		}
	}
}

bool UAbility_Telekinesis::RayCastObjects()
{
	bool bFoundObjects = false;
	if (OwnerActor.IsValid())
	{
		if (const UWorld* const World = OwnerActor->GetWorld())
		{
			const FVector CharacterLocation = OwnerActor->GetActorLocation();
			const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(TelekinesisRadius);

			TArray<FHitResult> HitResults;
			if	(World->SweepMultiByChannel(HitResults, CharacterLocation,
				CharacterLocation,
				FQuat(0.0f), ECollisionChannel::ECC_GameTraceChannel1, 
				CollisionShape, FCollisionQueryParams()))
			{
				for (const FHitResult& HitResult : HitResults)
				{
					bFoundObjects = true;
					if (TObjectPtr<ALevitatingActor> LevitatingActor = Cast<ALevitatingActor>(HitResult.GetActor()))
					{
						LevitatingActor->RequestLevitation(OwnerActor.Get());
						LevitatingActors.Add(LevitatingActor);	
					}
				}
			}
		}
	}

	return bFoundObjects;
}

void UAbility_Telekinesis::ReleaseObjects()
{
	for (const TObjectPtr<ALevitatingActor>& LevitatingActor : LevitatingActors)
	{
		if (LevitatingActor)
		{
			LevitatingActor->ResetActor();
		}
	}
	LevitatingActors.Empty();
}