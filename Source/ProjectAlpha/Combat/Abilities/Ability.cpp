// Copyright 2023 mozahzah. All Rights Reserved.

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"

void UAbility::Initialize(AActor* Actor)
{
	if (Actor)
	{
		OwnerActor = Actor;
		if (const ACharacter* const Character = Cast<ACharacter>(Actor)) 
		{
			OwnerController = Character->GetController();
		}

		if (USkeletalMeshComponent* SkeletalMeshComp = Actor->FindComponentByClass<USkeletalMeshComponent>())
		{
			SkeletalMeshComponent = SkeletalMeshComp;
		}

		AbilityParticleSystemComponent = NewObject<UParticleSystemComponent>(Actor, FName(TEXT("Ability_ParticleSystemComponent")), EObjectFlags::RF_Transient);
		if (AbilityParticleSystemComponent)
		{
			USceneComponent* SceneComponent = Actor->GetRootComponent();
			if (SkeletalMeshComponent.IsValid()) 
			{
				SceneComponent = SkeletalMeshComponent.Get();
			}

			AbilityParticleSystemComponent->SetupAttachment(SceneComponent, AbilitySocketName);
			AbilityParticleSystemComponent->RegisterComponent();
		}
	}

	OnInitialize();
}

void UAbility::Activate()
{
	bool bSuccess = false;
	OnActivate(bSuccess);

	if (bSuccess)
	{
		if (AbilityParticleSystemComponent && AbilityActivatedVFXEvent)
		{
			AbilityParticleSystemComponent->Template = AbilityActivatedVFXEvent;
			AbilityParticleSystemComponent->Activate();
		}

		if (SkeletalMeshComponent.IsValid() && AnimationMontage) 
		{
			SkeletalMeshComponent->PlayAnimation(AnimationMontage, bAnimLooping);
		}
	}
}

void UAbility::Update(float DeltaTime)
{
	if (bAbilityIsActive)
	{
		OnUpdate(DeltaTime);
	}
}

void UAbility::Deactivate()
{
	if (AbilityParticleSystemComponent)
	{
		AbilityParticleSystemComponent->Deactivate();
	}

	OnDeactivate();
}

void UAbility::StartFire()
{
	OnFireStart();
}

void UAbility::StopFire()
{
	OnFireStop();
}

void UAbility::StartSecondaryFire()
{
	OnSecondaryFireStart();
}

void UAbility::StopSecondaryFire()
{
	OnSecondaryFireStop();
}