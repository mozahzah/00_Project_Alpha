// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilityBase.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTALPHA_API UAbilityBase : public UObject 
{
	GENERATED_BODY()

protected:
	virtual void Initialize();
	virtual void Update(float DeltaTime);

public:

};