// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Ability.generated.h"

class UAkComponent;
class UAkAudioEvent;
class UParticleSystem;
class UParticleSystemComponent;

UCLASS(EditInlineNew)
class PROJECTALPHA_API UAbility : public UObject 
{
	GENERATED_BODY()

public:
	void Initialize(AActor* Actor);
	void Activate();
	void Update(const float& DeltaTime);
	void Deactivate();

	void Fire(const FVector& TargetLocation);
	void StopFire();
	void SecondaryFire();
	void StopSecondaryFire();

protected:
	virtual void OnInitialize() {};
	virtual void OnActivate() {};
	virtual void OnUpdate(const float& DeltaTime) {};
	virtual void OnDeactivate() {};

	virtual void OnFire(const FVector& TargetLocation) {};
	virtual void OnFireStop() {};
	virtual void OnSecondaryFire() {};
	virtual void OnSecondaryFireStop() {};

private:
	UPROPERTY(Transient)
	TObjectPtr<UAkComponent> AbilityAkComponent;

	UPROPERTY(Transient)
	TObjectPtr<UParticleSystemComponent> AbilityParticleSystemComponent;

	/*Activation delay in seconds */
	UPROPERTY(EditAnywhere, meta =(ClampMin = "0", UIMin = "0"))
	float ActivationDelay = 0.0f;

	/*Name of the socket to attach the ak component*/
	UPROPERTY(EditAnywhere)
	FName AbilitySocketName = FName(TEXT("body"));

	/*Audio event that will be posted when the ability activates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkAudioEvent> AbilityActivatedAudioEvent;

	/*Audio event that will be posted when the ability deactivates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkAudioEvent> AbilityDeactivedAudioEvent;

	/*VFX event that will be played when the ability activates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> AbilityActivatedVFXEvent;

	/*VFX event that will be played when the ability deactivates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> AbilityDeactivedVFXEvent;

protected:
	TWeakObjectPtr<AActor> OwnerActor;

private:
	float AbilityTimer;
	bool bAbilityIsActive;
};