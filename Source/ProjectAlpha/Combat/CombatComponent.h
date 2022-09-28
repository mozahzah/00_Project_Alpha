// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CombatComponent.generated.h"

enum class EAbility : uint8
{
	Movement,
	Controller,
	Ultimate,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTALPHA_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

private:
	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateAbility(EAbility Ability);
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
	UPROPERTY(EditAnywhere)
	TMap<EAbility, TObjectPtr<UAbility>> AbilityMap;

private:
	TWeakObjectPtr<APlayerController> PlayerController;
	TWeakObjectPtr<UAbility> CurrentAbility;
};
