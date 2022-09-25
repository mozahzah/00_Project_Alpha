// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ProjectAlphaAIController.generated.h"



UENUM()
enum EAIState
{
	Attacking,
	Suspicious,
	Petrolling
};

UCLASS()
class PROJECTALPHA_API AProjectAlphaAIController : public AAIController
{
	GENERATED_BODY()

protected: 
	void BeginPlay() override;
	bool CheckForCover();
	void Attacking();
	UPROPERTY() APawn* PlayerPawn = nullptr;
public:
	void Tick(float DeltaSeconds) override;

	
	

private:
	EAIState  CurrentAIState;

	void PetrolArea();


	FVector StartLocation;
	FVector EndLocation;
	FVector TargetLocation;
	FVector CoverLocation;


	FVector LastPlayerLocation;
	float TimeLastSeen;

	void MoveToCover(FVector CoverLocation);
	
	
};
