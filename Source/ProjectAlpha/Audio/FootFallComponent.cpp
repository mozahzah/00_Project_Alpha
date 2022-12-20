// Copyright 2023 mozahzah. All Rights Reserved.
#include "ProjectAlpha/Audio/FootFallComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include "FMODAudioComponent.h"
#include "FMODEvent.h"

namespace FootFallComponentUtil 
{
	static constexpr float CharacterVelocityParamMidpoint = 0.5f;
}

UFootFallComponent::UFootFallComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	LeftFootFMODAudioComponent = CreateDefaultSubobject<UFMODAudioComponent>("LeftFootFMODAudioComponent");
	RightFootFMODAudioComponent = CreateDefaultSubobject<UFMODAudioComponent>("RightFootFMODAudioComponent");
}

void UFootFallComponent::BeginPlay() 
{
	Super::BeginPlay();

	if (const UWorld* const World = GetWorld())
	{
		RefreshIntervalTimer = World->GetTimeSeconds();
	}

	if (AActor* const Owner = GetOwner(); ensureMsgf(Owner, TEXT("FootFallComponent must have an owner actor!")))
	{
		if (UCharacterMovementComponent* const CharacterMovementComp = Owner->FindComponentByClass<UCharacterMovementComponent>())
		{
			CharacterMovementComponent = CharacterMovementComp;
		}

		if (USkeletalMeshComponent* const SkeletelMeshComp = Owner->FindComponentByClass<USkeletalMeshComponent>())
		{
			SkeletelMeshComponent = SkeletelMeshComp;

			/* Initialization */
			for (auto& FootData : FootFallComponentData.FootDataMap) 
			{
				if (!FootData.Value.ToeSocketName.IsNone())
				{
					FootData.Value.SocketHeight.Add(FootData.Value.ToeSocketName, 0.0f);
				}

				/* Setup */
				if (FootData.Key == EFootFallFoot::Left && LeftFootFMODAudioComponent)
				{
					LeftFootFMODAudioComponent->Event = FootstepAudioEvent;
					if (!FootData.Value.HeelSocketName.IsNone())
					{
						LeftFootFMODAudioComponent->AttachToComponent(SkeletelMeshComponent.Get(), FAttachmentTransformRules::KeepRelativeTransform, FootData.Value.HeelSocketName);
						FootData.Value.SocketHeight.Add(FootData.Value.HeelSocketName, 0.0f);
					}
					else
					{
						LeftFootFMODAudioComponent->AttachToComponent(SkeletelMeshComponent.Get(), FAttachmentTransformRules::KeepRelativeTransform, FName("root"));
					}
				}

				if (FootData.Key == EFootFallFoot::Right && RightFootFMODAudioComponent)
				{
					RightFootFMODAudioComponent->Event = FootstepAudioEvent;
					if (!FootData.Value.HeelSocketName.IsNone())
					{
						RightFootFMODAudioComponent->AttachToComponent(SkeletelMeshComponent.Get(), FAttachmentTransformRules::KeepRelativeTransform, FootData.Value.HeelSocketName);
						FootData.Value.SocketHeight.Add(FootData.Value.HeelSocketName, 0.0f);
					}
					else
					{
						RightFootFMODAudioComponent->AttachToComponent(RightFootFMODAudioComponent.Get(), FAttachmentTransformRules::KeepRelativeTransform, FName("root"));
					}
				}
			}
		}
	}
}

void UFootFallComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	if (LeftFootFMODAudioComponent) 
	{
		LeftFootFMODAudioComponent->DestroyComponent();
		LeftFootFMODAudioComponent = nullptr;
	}
	if (RightFootFMODAudioComponent) 
	{
		RightFootFMODAudioComponent->DestroyComponent();
		RightFootFMODAudioComponent = nullptr;
	}

	CharacterMovementComponent.Reset();
	SkeletelMeshComponent.Reset();
}

void UFootFallComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateFootFallGeneralData(DeltaTime);

	static const UEnum* const FootFallEnum = StaticEnum<EFootFallFoot>();
	for (int32 Index = 0, Count = FootFallEnum->NumEnums() - 1; Index < Count; Index++)
	{
		const EFootFallFoot Foot = static_cast<EFootFallFoot>(FootFallEnum->GetValueByIndex(Index));
		UpdateFootFallFootData(Foot, DeltaTime);

		if (FFootData* const FootData = FootFallComponentData.FootDataMap.Find(Foot))
		{
			if (IsFootInFront(Foot))
			{
				FootData->CurrentFootStatus = EFootStatus::InFront;
				if (IsFootDown(Foot))
				{
					FootData->CurrentFootStatus = EFootStatus::OnGround;
					if (!FootData->bHasPlayed)
					{
						FootData->bHasPlayed = ProcessFootStepSound(Foot);
						FootFallComponentData.CurrentFootStepIndex++;
					}
				}
			}
			else if (!IsFootDown(Foot))
			{
				FootData->bHasPlayed = false;
				FootData->CurrentFootStatus = EFootStatus::InAir;
			}
		}
	}
	
}

void UFootFallComponent::UpdateMovementDirection()
{
	const int32 BodyboneIndex = SkeletelMeshComponent->GetBoneIndex(FName("body"));
	const FVector BodyDirection = SkeletelMeshComponent->GetBoneTransform(BodyboneIndex).TransformVector(FVector::UpVector);
	const float DotProduct = FVector::DotProduct(FootFallComponentData.CharacterVelocity.GetSafeNormal(), BodyDirection);

	FootFallComponentData.CurrentDirection = DotProduct >= 0.f ? EMovementDirection::Forward : EMovementDirection::Backward;
}

FName UFootFallComponent::GetCurrentSocket(const EFootFallFoot Foot) const
{
	FName SocketName;
	if (const FFootData* const FootData = FootFallComponentData.FootDataMap.Find(Foot))
	{
		SocketName = FootFallComponentData.CurrentDirection == EMovementDirection::Forward ? FootData->HeelSocketName : FootData->ToeSocketName;
	}

	return SocketName;
}

bool UFootFallComponent::IsFootInFront(const EFootFallFoot Foot)
{
	bool bIsFootInFront = false;

	if (FFootData* const FootData = FootFallComponentData.FootDataMap.Find(Foot)) 
	{
		if (FootFallComponentData.CharacterVelocity.Size() < MinimumSpeed)
		{
			FootFallComponentData.CurrentFootStepIndex = 0;
			if (IsFootDown(Foot))
			{
				FootData->CurrentFootStatus = EFootStatus::OnGround;
			}
		}
		else
		{
			bIsFootInFront = FootData->FootDotProduct > 0.f;
		}
	}
	
	return bIsFootInFront;
}

bool UFootFallComponent::IsFootDown(const EFootFallFoot Foot)
{
	float DynamicHeight = 0.f;
	if (CharacterMovementComponent.IsValid()) 
	{
		DynamicHeight = MinimumHeight + DynamicHeightAdjuster * FootFallComponentData.CurrentCharacterSpeedRatio;
	}

	bool bIsFootDown = false;
	if (const FFootData* const FootData = FootFallComponentData.FootDataMap.Find(Foot)) 
	{
		if (const float* const SocketHeight = FootData->SocketHeight.Find(GetCurrentSocket(Foot)))
		{
			bIsFootDown = *SocketHeight < DynamicHeight;
		}
	}

	return bIsFootDown;
}

float UFootFallComponent::GetSocketRelativeHeight(const FName& SocketName) const
{
	float SocketRootHeight = FLT_MAX;
	if (SkeletelMeshComponent.IsValid()) 
	{
		const FVector SocketLocation = SkeletelMeshComponent->GetSocketLocation(SocketName);
		const FVector RootLocation = SkeletelMeshComponent->GetBoneLocation(FName("root"));
		SocketRootHeight = SocketLocation.Z - RootLocation.Z;
	}

	return SocketRootHeight;
}

float UFootFallComponent::GetSocketFloorHeight(const FName& SocketName) const
{
	const FVector SocketLocation = SkeletelMeshComponent->GetSocketLocation(SocketName);
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());

	float SocketFloorHeight = FLT_MAX;
	if (GetWorld()->LineTraceSingleByChannel(Hit,
		SocketLocation,
		SocketLocation + FVector(0, 0, -TraceLength),
		ECollisionChannel::ECC_Visibility,
		TraceParams)) 
	{
		SocketFloorHeight = FVector::Distance(SocketLocation, Hit.Location);
	}

	return SocketFloorHeight;
}


void UFootFallComponent::UpdateFootFallGeneralData(float DeltaTime)
{
	UpdateMovementDirection();

	if (CharacterMovementComponent.IsValid())
	{
		FootFallComponentData.CharacterVelocity = CharacterMovementComponent->GetLastUpdateVelocity();
		FootFallComponentData.CurrentCharacterSpeedRatio = !FMath::IsNearlyZero(CharacterMovementComponent->MaxCustomMovementSpeed) ?
			FootFallComponentData.CharacterVelocity.Size() / CharacterMovementComponent->MaxCustomMovementSpeed : FootFallComponentUtil::CharacterVelocityParamMidpoint;
	}
}

void UFootFallComponent::UpdateFootFallFootData(const EFootFallFoot Foot, float DeltaTime)
{
	const FName SocketName = GetCurrentSocket(Foot);
	if (FFootData* const FootData = FootFallComponentData.FootDataMap.Find(Foot)) 
	{
		if (SkeletelMeshComponent.IsValid())
		{
			const FVector SocketLocation = SkeletelMeshComponent->GetSocketLocation(SocketName);

			if (FootData->CurrentFootStatus != EFootStatus::OnGround) 
			{
				FootData->CurrentSurfaceType = GetSurfaceMaterial(SocketLocation);
			}

			FootData->FootDotProduct = FVector::DotProduct((SocketLocation - SkeletelMeshComponent->GetBoneLocation(FName("root"))).GetSafeNormal(),
				(FootFallComponentData.CharacterVelocity.GetSafeNormal()));

			FootData->SocketHeight.Emplace(SocketName, GetSocketRelativeHeight(SocketName));
		}
	}
}

void UFootFallComponent::SendFootFallComponentDataToFMOD(const EFootFallFoot Foot, UFMODAudioComponent* FMODAudioComponent) const
{
	// TODO
}

EPhysicalSurface UFootFallComponent::GetSurfaceMaterial(const FVector SocketLocation) const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());
	TraceParams.bReturnPhysicalMaterial = true;

	EPhysicalSurface CurrentSurfaceType = EPhysicalSurface::SurfaceType_Default;
	if (GetWorld()->LineTraceSingleByChannel(Hit,
		SocketLocation,
		SocketLocation + FVector(0, 0, -TraceLength),
		ECollisionChannel::ECC_Visibility,
		TraceParams))
	{
		// Note: Hit.PhysMaterial must be validated before use
		const TWeakObjectPtr<class UPhysicalMaterial> PhysMaterial = Hit.PhysMaterial;
		if (PhysMaterial.IsValid())
		{
			CurrentSurfaceType = Hit.PhysMaterial->SurfaceType.GetValue();
		}
	}

	return CurrentSurfaceType;
}

bool UFootFallComponent::ProcessFootStepSound(EFootFallFoot Foot)
{
	bool bHasPlayed = false;

	UFMODAudioComponent* FMODAudioComponent = Foot == EFootFallFoot::Left ? LeftFootFMODAudioComponent : RightFootFMODAudioComponent;
	if (FMODAudioComponent && GetOwner())
	{
		if (GetWorld()->GetTimeSeconds() - RefreshIntervalTimer > RefreshInterval)
		{
			SendFootFallComponentDataToFMOD(Foot, FMODAudioComponent);

			FMODAudioComponent->Play();

			RefreshIntervalTimer = GetWorld()->GetTimeSeconds();
			bHasPlayed = true;
		}
	}

	return bHasPlayed;
}