// COPYRIGHT

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "Particles/ParticleSystemComponent.h"

void UAbility::Initialize(AActor* Actor)
{
	if (Actor)
	{
		OwnerActor = Actor;
		
		USceneComponent* SceneComponent = Actor->GetRootComponent();
		if (USkeletalMeshComponent* SkeletalMeshComponent = Actor->FindComponentByClass<USkeletalMeshComponent>())
		{
			SceneComponent = SkeletalMeshComponent;
		}

		AbilityParticleSystemComponent = NewObject<UParticleSystemComponent>(Actor, FName(TEXT("Ability_ParticleSystemComponent")), EObjectFlags::RF_Transient);
		if (AbilityParticleSystemComponent)
		{
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
		if (AbilityDeactivedVFXEvent)
		{
			AbilityParticleSystemComponent->Template = AbilityDeactivedVFXEvent;
			AbilityParticleSystemComponent->Activate();
		}
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

void UAbility::StartZoom()
{
	OnZoomStart();
}

void UAbility::StopZoom()
{
	OnZoomStop();
}

void UAbility::StartUnzoom()
{
	OnUnzoomStart();
}

void UAbility::StopUnzoom()
{
	OnUnzoomStop();
}