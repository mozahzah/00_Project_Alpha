// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectAlphaEnemyCharacter.generated.h"

UCLASS()
class PROJECTALPHA_API AProjectAlphaEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProjectAlphaEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	// AI PETROL AREA
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
    FVector FirstTarget;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
    FVector SecondTarget;

	UPROPERTY(EditAnywhere)
    float Health = 100.f;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
    UFUNCTION(BlueprintPure)
	float GetHealthPercent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDead = false;

	UFUNCTION(BlueprintCallable)
	void OnFootStepEvent();

	class UAkComponent* AkMainComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "Wwise")
	class UAkAudioEvent* FootStepEvent = nullptr;

	class UAkSwitchValue* CurrentSwitch = nullptr;
	UPROPERTY(EditAnywhere, Category = "Wwise")
	FString SurfaceType;
};
