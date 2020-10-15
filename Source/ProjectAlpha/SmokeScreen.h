// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SmokeScreen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTALPHA_API USmokeScreen : public UActorComponent
{
	GENERATED_BODY()

public:	

	USmokeScreen();

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	class ASmokeScreenActor* SmokeScreenActor;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmokeScreenActor> SmokeBlueprint;	


	void SetSmokeLocation(ASmokeScreenActor* SmokeActor);
	void ActivateSmokeScreen(FVector SmokeLocationToSet);
	void DeactivateSmokeScreen();

	FVector ForwardVector;
	FVector CurrentLocation;
	FVector EndLocation;


	bool bSmokeIsActive = false;

		
};
