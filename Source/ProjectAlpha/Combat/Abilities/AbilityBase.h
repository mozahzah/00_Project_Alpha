// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilityBase.generated.h"

UCLASS(EditInlineNew)
class PROJECTALPHA_API UAbilityBase : public UObject 
{
	GENERATED_BODY()

public:
	virtual void Initialize(AActor*& OwnerActor);
	virtual void Update(const float DeltaTime);
	virtual void ActivateAbility();
	virtual void DeactivateAbility();

protected:
	UPROPERTY(Transient)
	TObjectPtr<UAkComponent> AbilityAkComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkEvent> OnAbilityActived;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkEvent> OnAbilityDeactived;

protected:
	TWeakObjectPtr<AActor> OwnerActor;
};