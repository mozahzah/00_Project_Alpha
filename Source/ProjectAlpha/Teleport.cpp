// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"

#include "ProjectAlphaMainCharacter.h"
#include "Engine/Engine.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UTeleport::UTeleport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTeleport::BeginPlay()
{
	Super::BeginPlay();
	TeleportStartParticleSystem->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("neck_01"));
	TeleportEndParticleSystem->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("neck_01"));
		
}


// Called every frame
void UTeleport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bWeHaveTeleported) 
	{
		//Cast<ACharacter>(GetOwner())->GetController()->StopMovement();
		Cast<ACharacter>(GetOwner())->GetMovementComponent()->StopMovementImmediately();
		if (GetWorld()->GetTimeSeconds() - StartTeleportTime > (1 * 0.5))
		{
			Cast<ACharacter>(GetOwner())->GetMesh()->SetVisibility(false);
		}
		if (GetWorld()->GetTimeSeconds() - StartTeleportTime > (2 * 0.5))
		{
			SpawnPlayer(TeleportDestination);
		}
	}

	
	
}


void UTeleport::Teleport(FVector Destination)
{
	bTeleportIsActive = true;
	GetWorld()->GetWorldSettings()->SetTimeDilation(0.5);
	TeleportEndParticleSystem->Deactivate();
	TeleportStartParticleSystem->Activate();
	StartTeleportTime = GetWorld()->GetTimeSeconds();
	TeleportDestination = Destination;
	bWeHaveTeleported = true;
	
}

void UTeleport::SpawnPlayer(FVector Destination)
{
	if (!ensure(GetOwner())) return;	
	GetOwner()->SetActorLocation(Destination);
	GetWorld()->GetWorldSettings()->SetTimeDilation(1);
	TeleportStartParticleSystem->Deactivate();
	TeleportEndParticleSystem->Activate();
	Cast<ACharacter>(GetOwner())->GetMesh()->SetVisibility(true);
	bWeHaveTeleported = false;
	bTeleportIsActive = false;
}


void UTeleport::ActivateTeleport(FVector Destination)
{
	GEngine->AddOnScreenDebugMessage
    (
        1,
        3.f,
        FColor::Green,
        TEXT("Teleport Active")
    );
	
	
}

void UTeleport::DeactivateTeleport()
{
	GEngine->AddOnScreenDebugMessage
    (
        1,
        3.f,
        FColor::Green,
        TEXT("Teleport Inactive")
    );
	bTeleportIsActive = false;
}



