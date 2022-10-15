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
	void Initialize(AActor* OwnerActor);

	virtual void OnInitialize() {};
	virtual void Update(const float& DeltaTime) {};
	virtual bool ProcessLineTrace(const FVector& ViewpointLocation, const FRotator& ViewpointRotation, FVector& OuHitLocation) { return false; };
	virtual void OnActivate() {};
	virtual bool OnDeactivate() { return false; };

	// Firing Mechanics
	virtual void OnFire(const FVector& Location) {};
	virtual void OnFireStop() {};
	virtual void OnSecondaryFire() {};
	virtual void OnSecondaryFireStop() {};

protected:
	UPROPERTY(Transient)
	TObjectPtr<UAkComponent> AbilityAkComponent;

	UPROPERTY(Transient)
	TObjectPtr<UParticleSystemComponent> AbilityParticleSystemComponent;

protected:
	/*Activation delay in seconds */
	UPROPERTY(EditAnywhere, meta =(ClampMin = "0", UIMin = "0"))
	float ActivationDelay = 0.0f;

	/*Name of the socket to attach the ak component*/
	UPROPERTY(EditAnywhere)
	FName AbilitySocketName = FName(TEXT("body"));

	/*Audio event that will be posted when the ability activates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkAudioEvent> OnAbilityActivedAudioEvent;

	/*Audio event that will be posted when the ability deactivates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkAudioEvent> OnAbilityDeactivedAudioEvent;

	/*VFX event that will be played when the ability activates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> OnAbilityActivedVFXEvent;

	/*VFX event that will be played when the ability deactivates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> OnAbilityDeactivedVFXEvent;

protected:
	TWeakObjectPtr<AActor> OwnerActor;

	float AbilityTimer;
	bool bAbilityIsActive;
};