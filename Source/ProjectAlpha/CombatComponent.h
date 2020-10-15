// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UTelekinesis;
class ATelekineticObjects;
class UTeleport;
class AWeapon;
class USmokeScreen;


UENUM()
enum Abilities
{
	None,
	Telekinesis,
	Teleport,
	Weapon,
	SmokeScreen
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTALPHA_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	Abilities CurrentAbility;

	
	float LastFireTime;
	void SetReticle();
	void TelekinesisAimAt();
	void TeleportAimAt();
	void SmokeScreenAimAt();
	UTelekinesis* Telekinesis = nullptr;
	UTeleport* Teleport = nullptr;
	USmokeScreen* SmokeScreen = nullptr;
	AWeapon* Weapon = nullptr;

	TArray<ATelekineticObjects*> LevitatingObjects;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt();
	void Fire();
	void StopFire();
	void SecondaryFire();
	void StopSecondaryFire();
	bool bAddSmokeMousePressed = false;
	bool bMinusSmokeMousePressed = false;


	//For AimAt Method
	FVector ViewpointLocation;
	FRotator ViewpointRotation;
	FVector OutHitLocation;
	FVector EndLocation;
	float SmokeLenght;



	//Ability Activation
	void ActivateWeapon();
	void ActivateTelekinesis();
	void DeactivateTelekinesis();
	void ActivateTeleport();
	void DeactivateTeleport();
	void ActivateSmokeScreen();
	void DeactivateSmokeScreen();
	void FireSmoke();


	
	UPROPERTY(BlueprintReadOnly)
    bool bCTelekinesisIsActive = false;
	UPROPERTY(BlueprintReadOnly)
    bool bCTeleportIsActive = false;
	UPROPERTY(BlueprintReadOnly)
    bool bCWeaponIsActive = false;
	UPROPERTY(BlueprintReadOnly)
	bool bCSmokeIsActive = false;



};
