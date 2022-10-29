// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_Telekinesis.h"

#include "Particles/ParticleSystemComponent.h"

#include "ProjectAlpha/GamePlayActors/LevitatingActor.h"

void UAbility_Telekinesis::OnInitialize()
{

}

void UAbility_Telekinesis::OnUpdate(float DeltaTime)
{
	// Grabbed actor update
}

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
	if (!LevitatingActors.IsEmpty()) 
	{
		if (TObjectPtr<ALevitatingActor> LevitatingActor = LevitatingActors.Pop())
		{
			// Shoot actor towards location
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
			const FQuat Rotation = OwnerActor->GetActorRotation().Quaternion();
			const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(TelekinesisRadius);

			TArray<FHitResult> HitResults;
			if (GetWorld()->SweepMultiByChannel(HitResults, CharacterLocation, CharacterLocation, Rotation, ECollisionChannel::ECC_GameTraceChannel1, CollisionShape, FCollisionQueryParams()))
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