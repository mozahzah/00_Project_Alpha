// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ProjectAlphaMainCharacter.generated.h"

class UCombatComponent;

UCLASS()
class PROJECTALPHA_API AProjectAlphaMainCharacter : public ACharacter
{
	GENERATED_BODY()

	AProjectAlphaMainCharacter();

protected:
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	void MoveForward(const float Value);

	UFUNCTION()
	void MoveRight(const float Value);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCombatComponent> CombatComponent;

};