// Copyright 2023 mozahzah. All Rights Reserved.

#include "ProjectAlphaEnemyCharacter.h"

#include "AIController.h"

float AProjectAlphaEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount;
	if (FMath::IsNearlyZero(CurrentHealth))
	{
		if (AController* const CharController = GetController()) 
		{
			CharController->StopMovement();
		}
		SetActorEnableCollision(false);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

#if WITH_EDITOR
void AProjectAlphaEnemyCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property && 
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AProjectAlphaEnemyCharacter, MaxHealth))
	{
		if (CurrentHealth > MaxHealth) 
		{
			CurrentHealth = MaxHealth;
		}
	}
}
#endif