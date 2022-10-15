// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Ability_Teleport.generated.h"

UCLASS()
class PROJECTALPHA_API UAbility_Teleport : public UAbility
{
	GENERATED_BODY()

//protected:
//	// Begin Ability Implementation
//	void OnInitialize() override;
//	void Update(const float DeltaTime) override;
//	bool ProcessLineTrace(const FVector& ViewpointLocation, const FRotator& ViewpointRotation) override;
//	void ActivateAbility() override;
//	void OnFire() override;
//	void OnFireStop() override;
//	void DeactivateAbility() override;
//	// End Ability Implementation
//
//private:
//	void Teleport(const FVector& Destination);
//
//	bool bTeleportIsActive = false;
//
//	float StartTeleportTime = 0;
//
//
//	
//
//	bool bWeHaveTeleported = false;
//
//	void UCombatComponent::TeleportAimAt()
//	{
//		//Line Tracing 1
//		FHitResult OutHit1;
//		FVector Start1 = ViewpointLocation;
//		FVector End1 = ViewpointLocation + ViewpointRotation.Vector() * 1500;
//		if (GetWorld()->LineTraceSingleByChannel(OutHit1, Start1, End1, ECollisionChannel::ECC_Visibility))
//		{
//			OutHitLocation = OutHit1.Location;
//		}
//		else
//		{
//			//line Stracing 2
//			FHitResult OutHit2;
//			FVector Start2 = ViewpointLocation + ViewpointRotation.Vector() * 1500;
//			FVector End2 = Start2.DownVector * 500000;
//			if (GetWorld()->LineTraceSingleByChannel(OutHit2, Start2, End2, ECollisionChannel::ECC_Visibility))
//			{
//				OutHitLocation = OutHit2.Location;
//			}
//		}
//		DrawDebugLine(
//			GetWorld(), OutHitLocation
//			, OutHitLocation, FColor::Blue, false, 0, 10, 10);
//	}
//
//	if (CurrentAbility == Abilities::Teleport)
//	{
//		StartTeleportTimer = GetWorld()->GetTimeSeconds();
//		bCTeleportIsActive = true;
//		OutHitLocation.Z += 100;
//		Teleport->Teleport(OutHitLocation);
//	}
};
