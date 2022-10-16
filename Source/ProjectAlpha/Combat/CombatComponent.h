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
	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateAbility(EAbilityType Ability);
	bool DeactivateCurrentAbility();

	// Ability Binds Section
	void ActivateMovementAbility();
	void ActivateControllerAbility();
	void ActivateUltimateAbility();

	// Firing Mechanics Binds Section
	void Fire();
	void StopFire();
	void SecondaryFire();
	void StopSecondaryFire();

private:
	UPROPERTY(EditAnywhere, Instanced)
	TMap<EAbilityType, TObjectPtr<UAbility>> AbilityMap;

private:
	TWeakObjectPtr<APlayerController> PlayerController;
	TWeakObjectPtr<UAbility> CurrentAbility;
};