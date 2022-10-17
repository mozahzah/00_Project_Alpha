// COPYRIGHT

#include "ProjectAlpha/Combat/Abilities/Ability.h"

#include "Particles/ParticleSystemComponent.h"

#include "AkComponent.h"

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

		AbilityAkComponent = NewObject<UAkComponent>(Actor, FName(TEXT("Ability_AkComponent")), EObjectFlags::RF_Transient);
		if (AbilityAkComponent)
		{
			AbilityAkComponent->SetupAttachment(SceneComponent, AbilitySocketName);
			AbilityAkComponent->RegisterComponent();
		}

		AbilityParticleSystemComponent = NewObject<UParticleSystemComponent>(Actor, FName(TEXT("Ability_ParticleSystemComponent")), EObjectFlags::RF_Transient);
		if (AbilityParticleSystemComponent)
		{
			AbilityParticleSystemComponent->SetupAttachment(SceneComponent, AbilitySocketName);
			AbilityParticleSystemComponent->RegisterComponent();
		}

		OnInitialize();
	}
}

void UAbility::Activate()
{
	if (AbilityAkComponent && AbilityActivatedAudioEvent)
	{
		AbilityAkComponent->PostAkEvent(AbilityActivatedAudioEvent, 0, FOnAkPostEventCallback(), FString());
	}

	if (AbilityParticleSystemComponent && AbilityActivatedVFXEvent)
	{
		AbilityParticleSystemComponent->Template = AbilityActivatedVFXEvent;
		AbilityParticleSystemComponent->Activate();
	}

	OnActivate();
}

void UAbility::Update(const float& DeltaTime)
{
	if (bAbilityIsActive)
	{
		OnUpdate(DeltaTime);
	}
}

void UAbility::Deactivate()
{
	if (AbilityAkComponent)
	{
		AbilityAkComponent->Stop();
		if (AbilityDeactivedAudioEvent)
		{
			AbilityAkComponent->PostAkEvent(AbilityDeactivedAudioEvent, 0, FOnAkPostEventCallback(), FString());
		}
	}

	if (AbilityParticleSystemComponent)
	{
		AbilityParticleSystemComponent->Deactivate();
		if (AbilityDeactivedVFXEvent)
		{
			AbilityParticleSystemComponent->Template = AbilityDeactivedVFXEvent;
			AbilityParticleSystemComponent->Activate();
		}
	}

	OnDeactivated();
}

void UAbility::Fire(const FVector& TargetLocation)
{
	OnFire(TargetLocation);
}

void UAbility::StopFire()
{
	OnFireStop();
}

void UAbility::SecondaryFire()
{
	OnSecondaryFire();
}

void UAbility::StopSecondaryFire()
{
	OnSecondaryFireStop();
}