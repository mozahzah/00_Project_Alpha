// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "Ability_SmokeScreen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTALPHA_API UAbility_SmokeScreen : public UAbility
{
	GENERATED_BODY()

protected:
	// Begin Ability Implementation
	void OnInitialize() override;
	void Update(const float DeltaTime) override;
	bool ProcessLineTrace(const FVector& ViewpointLocation, const FRotator& ViewpointRotation) override;
	void ActivateAbility() override;
	void OnFire() override;
	void OnFireStop() override;
	void DeactivateAbility() override;
	// End Ability Implementation

private:
	void SetSmokeLocation(ASmokeScreenActor* SmokeActor);
	void ActivateSmokeScreen(FVector SmokeLocationToSet);

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmokeScreenActor> SmokeActor;

private:
	FVector ForwardVector;
	FVector CurrentLocation;
	FVector EndLocation;

	void UCombatComponent::SmokeScreenAimAt()
	{
		if (Cast<AProjectAlphaMainCharacter>(GetOwner())->GetPreSmoke() != nullptr)
		{
			if (!bPreSmokeisActive)
			{
				UE_LOG(LogTemp, Warning, TEXT("PreSmokeActive"));
				bPreSmokeisActive = true;
				const FActorSpawnParameters SpawnParameters;
				PreSmoke = GetWorld()->SpawnActor<APreSmokeActor>(Cast<AProjectAlphaMainCharacter>(GetOwner())->GetPreSmoke(), GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParameters);
			}
			PreSmoke->SetActorLocation(EndLocation);
		}
	}


	if (CurrentAbility == Abilities::SmokeScreen)
	{
		bAddSmokeMousePressed = true;
	}

	//void UCombatComponent::ActivateSmokeScreen()
//{
//	DeactivateTeleport();
//	DeactivateTelekinesis();
//	CurrentAbility = Abilities::SmokeScreen;
//	GetOwner()->InputComponent->RemoveActionBinding(12);
//	GetOwner()->InputComponent->BindAction(FName("ActivateSmokeScreen"), EInputEvent::IE_Pressed, this, &UCombatComponent::FireSmoke);
//	bCSmokeIsActive = true;
//}
//
//void UCombatComponent::DeactivateSmokeScreen() 
//{
//	bPreSmokeisActive = false;
//	if (PreSmoke != nullptr)
//	{
//		PreSmoke->Destroy();
//	}
//	bCSmokeIsActive = false;
//	bMinusSmokeMousePressed = false;
//	bAddSmokeMousePressed = false;
//	SmokeLenght = 0;
//	CurrentAbility = Abilities::Weapon;
//	GetOwner()->InputComponent->RemoveActionBinding(12);
//	GetOwner()->InputComponent->BindAction(FName("ActivateSmokeScreen"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateSmokeScreen);
//}
};
