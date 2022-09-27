// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "ProjectAlpha/Combat/Abilities/AbilityBase.h"

#include "ProjectAlpha/OtherActors/TelekineticObjects.h"

#include "Telekinesis.generated.h"

class ATelekineticObjects;
class UPrimitiveComponent;
class EAbility;

UCLASS()
class PROJECTALPHA_API UAbility_Telekinesis : public UAbilityBase
{
	GENERATED_BODY()

protected:
	// Begin AbilityBase Implementation
	void Initialize(AActor*& OwnerActor) override;
	void Update(const float DeltaTime) override;
	void ActivateAbility() override;
	void DeactivateAbility() override;
	// End AbilityBase Implementation

private:
	bool RayCastObjects();
	void LevitateObjects(float DeltaTime);
	void GetPhysicsHandler();
	void ReleaseObjects();

private:
	TArray<TObjectPtr<ATelekineticObjects>> GrabbedComponents;
    TArray<FKineticObjectData> KineticObjectDataArray;

	FVector CharacterLocation;

	UPROPERTY()
	float Radius = 500.f;



public:

	
	
	UFUNCTION(BlueprintCallable)


	
	
	UPROPERTY()



	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandler = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* MagicLeftHand;

	UPROPERTY(EditAnywhere)
    UParticleSystemComponent* MagicRightHand;

	float LevitationDelay;
};
