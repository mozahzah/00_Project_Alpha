// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "Ability_Teleport.generated.h"

UCLASS()
class PROJECTALPHA_API UAbility_Teleport : public UAbility
{
	GENERATED_BODY()

protected:
	// Begin Ability Implementation
	void OnActivate(bool& bSuccess) override;
	void OnUpdate(float DeltaTime) override;
	void OnDeactivate() override;
	void OnFireStart() override;
	// End Ability Implementation
//
private:
	void ProcessLineTrace();
	void Teleport();

private:
	/* Time it takes to teleport the actor in seconds*/
	UPROPERTY(EditAnywhere)
	float TeleportTime = 1.f;

	/* Max line trace distance of the teleport */
	UPROPERTY(EditAnywhere)
	float TeleportMaxLineTrace = 1000.f;

private:
	FVector CurrentTeleportLocation;
	float Timer;
	bool bIsTeleporting = false;
};
