// Copyright 2023 mozahzah. All Rights Reserved.

#include "ProjectAlpha/Audio/DynamicAudioPerception.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

#include "FMODAudioComponentTrackerSubsystem.h"
#include "FMODAudioComponent.h"
#include "FMODEvent.h"

UDynamicAudioPerception::UDynamicAudioPerception()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UDynamicAudioPerception::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* const World = GetWorld())
	{
		FMODAudioComponentTrackerSubsystem = World->GetSubsystem<UFMODAudioComponentTrackerSubsystem>();
	}

	if (const ACharacter* const Character = Cast<ACharacter>(GetOwner()))
	{
		PlayerController = Cast<APlayerController>(Character->GetController());
	}
}

void UDynamicAudioPerception::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEnable)
	{
		ProcessDynamicAudioPerception();
	}
}

void UDynamicAudioPerception::ProcessDynamicAudioPerception()
{
	if (FMODAudioComponentTrackerSubsystem.IsValid() && PlayerController.IsValid())
	{
		FVector ViewpointLocation;
		FRotator ViewpointRotation;
		PlayerController->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);

		for (const TWeakObjectPtr<UFMODAudioComponent>& FMODAudioComponent : FMODAudioComponentTrackerSubsystem->GetFMODAudioComponents())
		{
			if (FMODAudioComponent.IsValid())
			{
				const FVector FMODAudioComponentLocation = FMODAudioComponent->GetComponentLocation();
				const FVector VectorToComponent = (FMODAudioComponentLocation - ViewpointLocation).GetSafeNormal();
				const float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(VectorToComponent, ViewpointRotation.Vector())));
				const float AngleRatio = 1.0f - (Angle / 180.0f);

				FMODAudioComponent->SetParameter(ParameterName, AngleRatio);
			}
		}
	}
}