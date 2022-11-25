// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Ability.generated.h"

UENUM()
enum class EAbilityType : uint8
{
	Movement,
	Controller,
	Ultimate,
};

class UAnimMontage;
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

protected:
	virtual void OnInitialize() {};
	virtual void OnActivate(bool& bSuccess) {};
	virtual void OnUpdate(float DeltaTime) {};
	virtual void OnDeactivate() {};

	virtual void OnFireStart() {};
	virtual void OnFireStop() {};
	virtual void OnSecondaryFireStart() {};
	virtual void OnSecondaryFireStop() {};

protected:
	UPROPERTY(Transient)
	TObjectPtr<UParticleSystemComponent> AbilityParticleSystemComponent;

	/*Name of the socket to attach the ak component*/
	UPROPERTY(EditAnywhere)
	FName AbilitySocketName = FName(TEXT("body"));

	/*VFX event that will be played when the ability activates*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> AbilityActivatedVFXEvent;

	/*Animation Montage to play for this ability*/
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AnimationMontage;

	/*If the animation montage is looping*/
	UPROPERTY(EditAnywhere)
	bool bAnimLooping = false;

protected:
	TWeakObjectPtr<AActor> OwnerActor;
	TWeakObjectPtr<AController> OwnerController;
	float AbilityTimer;
	bool bAbilityIsActive;
	bool bIsLocked = false;

private:
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};