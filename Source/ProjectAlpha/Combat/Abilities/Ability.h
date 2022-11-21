// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Ability.generated.h"

class UParticleSystem;
class UParticleSystemComponent;

UCLASS(EditInlineNew)
class PROJECTALPHA_API UAbility : public UObject 
{
	GENERATED_BODY()

public:
	void Initialize(AActor* Actor);
	void Activate();
	void Update(float DeltaTime);
	void Deactivate();
	bool IsLocked() const { return bIsLocked; };

	void StartFire();
	void StopFire();
	void StartSecondaryFire();
	void StopSecondaryFire();
	void StartZoom();
	void StopZoom();
	void StartUnzoom();
	void StopUnzoom();


protected:
	virtual void OnInitialize() {};
	virtual void OnActivate(bool& bSuccess) {};
	virtual void OnUpdate(float DeltaTime) {};
	virtual void OnDeactivate() {};

	virtual void OnFireStart() {};
	virtual void OnFireStop() {};
	virtual void OnSecondaryFireStart() {};
	virtual void OnSecondaryFireStop() {};
	virtual void OnZoomStart() {};
	virtual void OnZoomStop() {};
	virtual void OnUnzoomStart() {};
	virtual void OnUnzoomStop() {};

protected:
	UPROPERTY(Transient)
	TObjectPtr<UParticleSystemComponent> AbilityParticleSystemComponent;

	/*Activation delay in seconds */
	UPROPERTY(EditAnywhere, meta =(ClampMin = "0", UIMin = "0"))
	float ActivationDelay = 0.0f;

	/*Name of the socket to attach the ak component*/
	UPROPERTY(EditAnywhere)
	FName AbilitySocketName = FName(TEXT("body"));

	/*VFX event that will be played when the ability activates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> AbilityActivatedVFXEvent;

	/*VFX event that will be played when the ability deactivates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> AbilityDeactivedVFXEvent;

protected:
	TWeakObjectPtr<AActor> OwnerActor;
	float AbilityTimer;
	bool bAbilityIsActive;
	bool bIsLocked = false;
};