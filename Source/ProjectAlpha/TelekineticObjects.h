// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"

#include "TelekineticObjects.generated.h"

USTRUCT()
struct FKineticObjectData
{
	GENERATED_BODY()
    float Distance;
	FRotator Direction;
	
};


class UParticleSystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTALPHA_API ATelekineticObjects : public AStaticMeshActor
{
	GENERATED_BODY()
protected:
	ATelekineticObjects();
	virtual void BeginPlay() override;
	
	void GetParticleSystem();
	
	

	
	UParticleSystemComponent* TelekineticObjectParticleFx;
	

public:
	
	void Tick(float DeltaSeconds);
	void SetObjectLocation(FVector CharacterLocation, FKineticObjectData ObjectData, float DeltaTime);
	void ActivateParticleSystem();
	void DeactivateParticleSystem();
	void ResetObject();

	FKineticObjectData KineticObjectData;
	UPROPERTY(EditAnywhere)
	bool bIsLevitated = false;
	float LevitationHeight = 0;
	float MaxHeight = 0;
	FVector CurrentLocation;

	int32 PlayingId;
	UPROPERTY(EditAnywhere, Category = "Wwise")
	class UAkAudioEvent* AkHitEvent;

	//UFUNCTION()
    //void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
    //const FHitResult& Hit);

	float ZValue;

	float RotationDelta;
	
};
