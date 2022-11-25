// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ProjectAlpha/Combat/Abilities/AbilityDataAsset.h"

#include "CombatComponent.generated.h"

UCLASS(BlueprintType)
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

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr <UAbilityDataAsset> AbilityDataAsset;

private:
	TObjectPtr<UAbility> CurrentAbility;
};
