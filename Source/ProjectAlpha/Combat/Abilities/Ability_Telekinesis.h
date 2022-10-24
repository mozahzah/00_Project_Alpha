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
	void OnUpdate(float DeltaTime) override;
	void OnActivate(bool& bSuccess) override;
	void OnDeactivate() override;
	void OnFireStart() override;
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
