// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "Ability_Telekinesis.generated.h"

class ALevitatingActor;

UCLASS()
class PROJECTALPHA_API UAbility_Telekinesis : public UAbility
{
	GENERATED_BODY()

protected:
	// Begin Ability Implementation
	void OnInitialize() override;
	void Update(const float& DeltaTime) override;
	bool ProcessLineTrace(const FVector& ViewpointLocation, const FRotator& ViewpointRotation, FVector& OutHitLocation) override;
	void OnActivate() override;
	bool OnDeactivate() override;
	void OnFire(const FVector& Location) override;
	// End Ability Implementation

private:
	bool RayCastObjects();
	void ReleaseObjects();

private:
	/* Radius for casting */
	UPROPERTY(EditAnywhere)
	float TelekinesisRadius = 500.0f;

private:
	TArray<TObjectPtr<ALevitatingActor>> LevitatingActors;
};
