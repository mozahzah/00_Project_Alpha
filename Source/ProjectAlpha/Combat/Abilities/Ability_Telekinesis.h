// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "ProjectAlpha/Combat/Abilities/Ability.h"
#include "ProjectAlpha/OtherActors/TelekineticObjects.h"

#include "Ability_Telekinesis.generated.h"

class ATelekineticObjects;
class UPrimitiveComponent;

UCLASS()
class PROJECTALPHA_API UAbility_Telekinesis : public UAbility
{
	GENERATED_BODY()

protected:
	// Begin Ability Implementation
	void OnInitialize() override;
	void Update(const float& DeltaTime) override;
	bool ProcessLineTrace(const FVector& ViewpointLocation, const FRotator& ViewpointRotation) override;
	void OnActivate() override;
	void OnDeactivate() override;
	void OnFire() override;
	// End Ability Implementation

private:
	bool RayCastObjects();
	void LevitateObjects(const float& DeltaTime);
	
	void ReleaseObjects();

	void GetPhysicsHandler();

private:
	TArray<TObjectPtr<ATelekineticObject>> GrabbedTelekineticObjects;
    TArray<FKineticObjectData> KineticObjectDataArray;

	FVector CharacterLocation;

	/* Radius for casting */
	UPROPERTY(EditAnywhere)
	float TelekinesisRadius = 500.0f;

	/* Trace channel for casting */
	UPROPERTY(EditAnywhere)
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_GameTraceChannel1;

	void UCombatComponent::TelekinesisAimAt()
	{
		FHitResult OutHit;
		FVector Start = ViewpointLocation;
		FVector End = ViewpointLocation + ViewpointRotation.Vector() * 1000000;
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility))
		{
			OutHitLocation = OutHit.Location;
		}
	}

	if (CurrentAbility == Abilities::Telekinesis)
	{
		auto LastGrabbedIndex = Telekinesis->GrabbedComponents.Num() - 1;
		if (LastGrabbedIndex < 0) return;
		auto Projectile = (Telekinesis->GrabbedComponents[LastGrabbedIndex]);
		if (!ensure(Projectile)) return;
		Telekinesis->GrabbedComponents.RemoveAt(LastGrabbedIndex);
		Telekinesis->PhysicsHandler->ReleaseComponent();
		Projectile->ResetObject();
		auto OutDirection = (OutHitLocation - Projectile->GetActorLocation()).GetSafeNormal();
		Projectile->GetStaticMeshComponent()->SetPhysicsLinearVelocity((OutDirection) * 10000.f);
		if (LastGrabbedIndex == 0) ActivateWeapon();
	}

public:

	
	
	UFUNCTION(BlueprintCallable)


	
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* MagicLeftHand;

	UPROPERTY(EditAnywhere)
    UParticleSystemComponent* MagicRightHand;

	float LevitationDelay;
};
