// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"

#include "Components/InputComponent.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	//Input Binding for Combat (Maybe not the best place to setup)
	if (const AActor* Owner = GetOwner())
	{
		if (UInputComponent* const InputComponent = Owner->InputComponent)
		{
			//InputComponent->BindAction(FName("ActivateMovementAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateMovementAbility);
			//InputComponent->BindAction(FName("ActivateControllerAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateControllerAbility);
			InputComponent->BindAction(FName("ActivateUltimateAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateUltimateAbility);

			InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &UCombatComponent::Fire);
			InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Released, this, &UCombatComponent::StopFire);

			InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Pressed, this, &UCombatComponent::Fire);
			InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Released, this, &UCombatComponent::StopFire);
		}
	}

	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (APlayerController* Controller = Cast<APlayerController>(Pawn->GetController()))
		{
			PlayerController = Controller;
		}
	}

	for (const TPair<EAbilityType, TObjectPtr<UAbility>>& Elem : AbilityMap)
	{
		TObjectPtr<UAbility> Ability = Elem.Value;
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
		if (CurrentAbility.IsValid())
		{
			CurrentAbility->Update(DeltaTime);
		}
	}	
}

void UCombatComponent::ActivateAbility(EAbilityType AbilityType)
{
	if (const TObjectPtr<UAbility>* Ability = AbilityMap.Find(AbilityType))
	{
		if (Ability && !Ability->IsNull())
		{
			CurrentAbility = Ability->Get();
			CurrentAbility->Activate();
		}
	}
}

bool UCombatComponent::DeactivateCurrentAbility()
{
	bool bHasDeactivated = true;
	if (CurrentAbility.IsValid())
	{
		CurrentAbility->Deactivate();
		return bHasDeactivated;
	}
}

// Ability Binds Section

void UCombatComponent::ActivateMovementAbility()
{
	if (DeactivateCurrentAbility())
	{
		ActivateAbility(EAbilityType::Movement);
	}
}

void UCombatComponent::ActivateControllerAbility()
{
	if (DeactivateCurrentAbility())
	{
		ActivateAbility(EAbilityType::Controller);
	}
}

void UCombatComponent::ActivateUltimateAbility()
{
	if (DeactivateCurrentAbility())
	{
		ActivateAbility(EAbilityType::Ultimate);
	}
}

// Firing Mechanics Binds Section

void UCombatComponent::Fire()
{
	if (CurrentAbility.IsValid())
	{
		CurrentAbility->Fire(FVector::ZeroVector);
	}
}

void UCombatComponent::StopFire()
{
	if (CurrentAbility.IsValid())
	{
		CurrentAbility->StopFire();
	}
}

void UCombatComponent::SecondaryFire()
{
	if (CurrentAbility.IsValid())
	{
		CurrentAbility->SecondaryFire();
	}
}

void UCombatComponent::StopSecondaryFire()
{
	if (CurrentAbility.IsValid())
	{
		CurrentAbility->StopSecondaryFire();
	}
}