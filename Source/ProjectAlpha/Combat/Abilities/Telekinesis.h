// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectAlpha/OtherActors/TelekineticObjects.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Telekinesis.generated.h"


class UPrimitiveComponent;
class ATelekineticObjects;
class EAbility;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTALPHA_API UTelekinesis : public UActorComponent
{
	GENERATED_BODY()

private:

    float LevitationDelay;


protected:
	virtual void BeginPlay() override;

	bool RayCastObjects();
	void LevitateObjects(float DeltaTime);

	void GetPhysicsHandler();

	EAbility* CurrentAbility;

	

	UPROPERTY()
    TArray<FKineticObjectData> KineticObjectDataArray;

	FVector CharacterLocation;
	UPROPERTY()
	float Radius = 500.f;

	class UAkComponent* AkMainComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "Wwise")
    class UAkAudioEvent* TelekinesisEvent = nullptr;
	int32 PlayingId;

public:
    UTelekinesis();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void ActivateTelekinesis();
	
	UFUNCTION(BlueprintCallable)
	void DeactivateTelekinesis();

	UPROPERTY(BlueprintReadOnly)
	bool bTelekinesisIsActive = false;
	
	UPROPERTY()
	TArray<ATelekineticObjects*> GrabbedComponents;

	void ReleaseObjects();

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandler = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* MagicLeftHand;

	UPROPERTY(EditAnywhere)
    UParticleSystemComponent* MagicRightHand;
};
