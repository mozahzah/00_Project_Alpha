// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ProjectAlpha/Combat/Abilities/Ability.h"
#include "ProjectAlpha/GameplayActors/SmokeScreenActor.h"

#include "Ability_SmokeScreen.generated.h"

UCLASS()
class PROJECTALPHA_API UAbility_SmokeScreen : public UAbility
{
	GENERATED_BODY()

protected:
	// Begin Ability Implementation
	void OnInitialize() override;
	void OnUpdate(float DeltaTime) override;
	void OnActivate(bool& bSuccess) override;
	void OnDeactivate() override;
	void OnFireStart() override;
	// End Ability Implementation

private:
	/* The smoke screen actor to use */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmokeScreenActor> SmokeScreenActor;

	/* Speed at which the smoke screen actor travels cm/s */
	UPROPERTY(EditAnywhere)
	float bDeployementSpeed = 500.f;

	/* The size of widget used to place the smoke actor */
	UPROPERTY(EditAnywhere)
	float PreSmokeWidgetSize = 50.0f;

private:
	TWeakObjectPtr<const UWorld> MyWorld;
	bool bSmokeHasBeenDeployed;

	float DistanceFromPlayer;
	FVector SmokeLocation;
};