// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"

#include "ProjectAlpha/Combat/Abilities/Teleport.h"
#include "DrawDebugHelpers.h"
#include "ProjectAlpha/Combat/Abilities/Telekinesis.h"
#include "ProjectAlpha/Combat/Abilities/Weapon.h"
#include "ProjectAlpha/Combat/Abilities/SmokeScreen.h"
#include "ProjectAlpha/GamePlayActors/PreSmokeActor.h"
#include "Components/InputComponent.h"
#include "ProjectAlpha/Characters/ProjectAlphaMainCharacter.h"
#include "Particles/ParticleSystemComponent.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//Input Binding for Combat (Maybe not the best place to setup)
	if (const AActor* Owner = GetOwner())
	{
		if (const UInputComponent* InputComponent = Owner->InputComponent)
		{
			InputComponent->BindAction(FName("ActivateMovementAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateMovementAbility);
			InputComponent->BindAction(FName("ActivateControllerAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateControllerAbility);
			InputComponent->BindAction(FName("ActivateUltimateAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateUltimateAbility);

			InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &UCombatComponent::Fire);
			InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Released, this, &UCombatComponent::StopFire);

			InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Pressed, this, &UCombatComponent::Fire);
			InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Released, this, &UCombatComponent::StopFire);
		}
	}
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (const APlayerController* PlayerController = Pawn->GetController())
		{
			this->PlayerController = PlayerController;
		}
	}

	for (const TObjectPtr<UAbility>& Ability : AbilityMap)
	{
		if (!Ability.IsNull())
		{
			Ability->Initialize(GetOwner());
		}	
	}
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PlayerController.IsValid())
	{
		if (CurrentAbility.IsValid() && CurrentAbility->bAbilityIsActive)
		{
			FVector ViewpointLocation;
			FRotator ViewpointRotation;
			PlayerController->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);
			if (CurrentAbility->ProcessLineTrace(ViewpointLocation, ViewpointRotation))
			{
				CurrentAbility->Update(DeltaTime);
			}
		}
	}	
}

void UCombatComponent::ActivateAbility(EAbility Ability)
{
	if (const TObjectPtr<UAbility>* Ability = AbilityMap.Find(Ability))
	{
		if (!Ability->IsNull())
		{
			CurrentAbility = Ability->Get();
			CurrentAbility->ActivateAbility();
		}
	}
}

void UCombatComponent::DeactivateCurrentAbility()
{
	bool bHasDeactivated = false;
	if (CurrentAbility.IsValid() && CurrentAbility->bAbilityIsActive)
	{
		bHasDeactivated = CurrentAbility->DeactivateAbility();
	}

	return bHasDeactivated;
}

// Ability Binds Section

void UCombatComponent::ActivateMovementAbility()
{
	if (DeactivateCurrentAbility())
	{
		ActivateAbility(EAbility::Movement);
	}
}

void UCombatComponent::ActivateControllerAbility()
{
	if (DeactivateCurrentAbility())
	{
		ActivateAbility(EAbility::Controller);
	}
}

void UCombatComponent::ActivateUltimateAbility()
{
	if (DeactivateCurrentAbility())
	{
		ActivateAbility(EAbility::Ultimate);
	}
}

// Firing Mechanics Binds Section

void UCombatComponent::Fire()
{
	if (CurrentAbility.IsValid() && CurrentAbility->bAbilityIsActive)
	{
		CurrentAbility->OnFire();
	}
}

void UCombatComponent::StopFire()
{
	if (CurrentAbility.IsValid() && CurrentAbility->bAbilityIsActive)
	{
		CurrentAbility->OnFireStop();
	}
}

void UCombatComponent::SecondaryFire()
{
	if (CurrentAbility.IsValid() && CurrentAbility->bAbilityIsActive)
	{
		CurrentAbility->OnSecondaryFire();
	}
}

void UCombatComponent::StopSecondaryFire()
{
	if (CurrentAbility.IsValid() && CurrentAbility->bAbilityIsActive)
	{
		CurrentAbility->OnSecondaryFireStop();
	}
}