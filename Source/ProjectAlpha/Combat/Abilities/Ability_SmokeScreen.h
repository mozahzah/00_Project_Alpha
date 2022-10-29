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
	void OnFireStop() override;
	// End Ability Implementation

private:
	/* The smoke screen actor to use */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmokeScreenActor> SmokeScreenActorClass;

	/* Speed at which the smoke screen actor travels cm/s */
	UPROPERTY(EditAnywhere)
	float SmokeDeployementSpeed = 500.f;

	/* The smoke screen actor to use */
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmokeScreenActor> PreSmokeScreenActorClass;

	/* Speed at which the smoke screen actor travels cm/s */
	UPROPERTY(EditAnywhere)
	float PreSmokeSpeed = 500.f;

private:
	UPROPERTY(Transient)
	TObjectPtr<ASmokeScreenActor> PreSmokeScreenActor;

private:
	TWeakObjectPtr<const UWorld> MyWorld;
	bool bSmokeHasBeenDeployed;

	float DistanceFromPlayer;
	FVector SmokeLocation;

	//bool bFireButtonIsHeld;
	//bool bSecondaryFireButtonHeld;
};