// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Teleport.generated.h"

class UParticleSystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTALPHA_API UTeleport : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleport();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ActivateTeleport(FVector Destination);
	UFUNCTION(BlueprintCallable)
	void DeactivateTeleport();
	bool bTeleportIsActive = false;
	void Teleport(FVector Destination);
	void SpawnPlayer(FVector Destination);

	float StartTeleportTime = 0;
	FVector TeleportDestination;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* TeleportStartParticleSystem;

	UPROPERTY(EditAnywhere)
    UParticleSystemComponent* TeleportEndParticleSystem;
	

	bool bWeHaveTeleported = false;

	

};
