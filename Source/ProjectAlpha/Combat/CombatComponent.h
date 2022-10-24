// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "CombatComponent.generated.h"

UENUM()
enum class EAbilityType : uint8
{
	Movement,
	Controller,
	Ultimate,
};

UCLASS()
class PROJECTALPHA_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

private:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateAbility(EAbilityType Ability);
	void DeactivateCurrentAbility();

	// Ability Binds Section
	void ActivateMovementAbility();
	void ActivateControllerAbility();
	void ActivateUltimateAbility();

	// Firing Mechanics Binds Section
	void StartFire();
	void StopFire();
	void StartSecondaryFire();
	void StopSecondaryFire();
	void StartZoom();
	void StopZoom();
	void StartUnzoom();
	void StopUnzoom();

private:
	UPROPERTY(EditDefaultsOnly, Instanced)
	TMap<EAbilityType, TObjectPtr<UAbility>> AbilityMap;

private:
	TObjectPtr<UAbility> CurrentAbility;
};