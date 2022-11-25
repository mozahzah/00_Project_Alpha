// Copyright 2023 mozahzah. All Rights Reserved.

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
			InputComponent->BindAction(FName("ActivateMovementAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateMovementAbility);
			InputComponent->BindAction(FName("ActivateControllerAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateControllerAbility);
			InputComponent->BindAction(FName("ActivateUltimateAbility"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateUltimateAbility);
			InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &UCombatComponent::StartFire);
			InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Released, this, &UCombatComponent::StopFire);
			InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Pressed, this, &UCombatComponent::StartSecondaryFire);
			InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Released, this, &UCombatComponent::StopSecondaryFire);
		}
	}

	if (AbilityDataAsset)
	{
		for (const TPair<EAbilityType, TObjectPtr<UAbility>>& Elem : AbilityDataAsset->GetAbilityMap())
		{
			TObjectPtr<UAbility> Ability = Elem.Value;
			if (Ability)
			{
				Ability->Initialize(GetOwner());
			}
		}
	}
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (CurrentAbility)
	{
		//TODO CHECK IF ACTIVE
		CurrentAbility->Update(DeltaTime);
	}
}

void UCombatComponent::ActivateAbility(EAbilityType AbilityType)
{
	if (AbilityDataAsset)
	{
		if (const TObjectPtr<UAbility>* AbilityPtr = AbilityDataAsset->GetAbilityMap().Find(AbilityType))
		{
			if (*AbilityPtr)
			{
				CurrentAbility = AbilityPtr->Get();
				CurrentAbility->Activate();
			}
		}
	}
}

void UCombatComponent::DeactivateCurrentAbility()
{
	if (CurrentAbility && !CurrentAbility->IsLocked())
	{
		CurrentAbility->Deactivate();
	}
}

// Ability Binds Section

void UCombatComponent::ActivateMovementAbility()
{
	DeactivateCurrentAbility();
	ActivateAbility(EAbilityType::Movement);
}

void UCombatComponent::ActivateControllerAbility()
{
	DeactivateCurrentAbility();
	ActivateAbility(EAbilityType::Controller);
}

void UCombatComponent::ActivateUltimateAbility()
{
	DeactivateCurrentAbility();
	ActivateAbility(EAbilityType::Ultimate);
}

// Firing Mechanics Binds Section

void UCombatComponent::StartFire()
{
	if (CurrentAbility)
	{
		CurrentAbility->StartFire();
	}
}

void UCombatComponent::StopFire()
{
	if (CurrentAbility)
	{
		CurrentAbility->StopFire();
	}
}

void UCombatComponent::StartSecondaryFire()
{
	if (CurrentAbility)
	{
		CurrentAbility->StartSecondaryFire();
	}
}

void UCombatComponent::StopSecondaryFire()
{
	if (CurrentAbility)
	{
		CurrentAbility->StopSecondaryFire();
	}
}