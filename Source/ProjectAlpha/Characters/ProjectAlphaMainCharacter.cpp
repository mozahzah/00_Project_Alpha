// Copyright 2023 mozahzah. All Rights Reserved.

#include "ProjectAlphaMainCharacter.h"

#include "Math/RotationMatrix.h"

#include "ProjectAlpha/Combat/CombatComponent.h"

AProjectAlphaMainCharacter::AProjectAlphaMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(FName(TEXT("Combat Component")));
}

void AProjectAlphaMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectAlphaMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectAlphaMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AProjectAlphaMainCharacter::MoveForward(const float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AProjectAlphaMainCharacter::MoveRight(const float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}