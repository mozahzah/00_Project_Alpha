// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "AbilityDataAsset.generated.h"

UCLASS()
class UAbilityDataAsset : public UPrimaryDataAsset 
{
	GENERATED_BODY()
	
public:
	const TMap<EAbilityType, TObjectPtr<UAbility>>& GetAbilityMap() const { return AbilityMap; }

private:
	UPROPERTY(EditAnywhere, Instanced)
	TMap<EAbilityType, TObjectPtr<UAbility>> AbilityMap;

};