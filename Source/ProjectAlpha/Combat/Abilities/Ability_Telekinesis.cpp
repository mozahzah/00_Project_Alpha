// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_Telekinesis.h"

#include "Particles/ParticleSystemComponent.h"

#include "AkComponent.h"

#include "ProjectAlpha/GamePlayActors/LevitatingActor.h"


void UAbility_Telekinesis::OnInitialize()
{

}

void UAbility_Telekinesis::Update(const float& DeltaTime)
{
	// Grabbed actor update
}

bool UAbility_Telekinesis::ProcessLineTrace(const FVector& ViewpointLocation, const FRotator& ViewpointRotation, FVector& OutHitLocation)
{
	bool bHasHit = false;
	FHitResult OutHit;
	FVector End = ViewpointLocation + (ViewpointRotation.Vector() * MAX_FLT);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, ViewpointLocation, End, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = OutHit.Location;
		bHasHit = true;
	}

	return bHasHit;
}

void UAbility_Telekinesis::OnActivate()
{
	if (RayCastObjects()) 
	{
		bAbilityIsActive = true;

		if (AbilityAkComponent)
		{
			AbilityAkComponent->PostAkEvent(OnAbilityActivedAudioEvent, 0, FOnAkPostEventCallback(), FString());
		}
		
		if (AbilityParticleSystemComponent)
		{
			AbilityParticleSystemComponent->Activate();
		}
	}
}


bool UAbility_Telekinesis::OnDeactivate()
{
	ReleaseObjects();
	bAbilityIsActive = false;
}

void UAbility_Telekinesis::OnFire(const FVector& Location)
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
					if (TObjectPtr<ALevitatingActor> LevitatingActor = Cast<ALevitatingActor>(HitResult.GetActor()))
					{
						LevitatingActor->LevitationRequested(OwnerActor.Get());
						LevitatingActors.Add(LevitatingActor);
						bFoundObjects = true;
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
		LevitatingActor->ResetActor();
	}
	LevitatingActors.Empty();
}