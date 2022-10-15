// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Teleport.h"



// Sets default values for this component's properties
//UTeleport::UTeleport()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UTeleport::BeginPlay()
//{
//	Super::BeginPlay();
//	TeleportStartParticleSystem->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("neck_01"));
//	TeleportEndParticleSystem->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("neck_01"));
//		
//}
//
//
//// Called every frame
//void UTeleport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	if (bWeHaveTeleported) 
//	{
//		Cast<ACharacter>(GetOwner())->DisableInput(Cast<APlayerController>(Cast<ACharacter>(GetOwner())->GetController()));
//		
//		if (GetWorld()->GetTimeSeconds() - StartTeleportTime > (1 * 0.5))
//		{
//			Cast<ACharacter>(GetOwner())->GetMesh()->SetVisibility(false);
//			SpawnPlayer(TeleportDestination);
//			Cast<AProjectAlphaMainCharacter>(GetOwner())->AddControllerYawInput(-285 * DeltaTime);
//		}
//		if (GetWorld()->GetTimeSeconds() - StartTeleportTime > (1.5 * 0.5))
//		{
//			Cast<ACharacter>(GetOwner())->GetMesh()->SetVisibility(true);
//			GetWorld()->GetWorldSettings()->SetTimeDilation(1);
//			bWeHaveTeleported = false;
//			Cast<ACharacter>(GetOwner())->EnableInput(Cast<APlayerController>(Cast<ACharacter>(GetOwner())->GetController()));
//		}
//	}
//}
//
//void UTeleport::Teleport(FVector Destination)
//{
//	bTeleportIsActive = true;
//	GetWorld()->GetWorldSettings()->SetTimeDilation(0.5);
//	TeleportEndParticleSystem->Deactivate();
//	TeleportStartParticleSystem->Activate();
//	StartTeleportTime = GetWorld()->GetTimeSeconds();
//	TeleportDestination = Destination;
//	bWeHaveTeleported = true;
//}
//
//void UTeleport::SpawnPlayer(FVector Destination)
//{
//	if (!ensure(GetOwner())) return;	
//	GetOwner()->SetActorLocation(Destination);
//	TeleportStartParticleSystem->Deactivate();
//	TeleportEndParticleSystem->Activate();
//	bTeleportIsActive = false;
//}
//
//
//
//
//
//void UTeleport::ActivateTeleport(FVector Destination)
//{
//	/*GEngine->AddOnScreenDebugMessage
//    (
//        1,
//        3.f,
//        FColor::Green,
//        TEXT("Teleport Active")
//    );*/
//	return;
//	
//}
//void UTeleport::DeactivateTeleport()
//{
//	/*GEngine->AddOnScreenDebugMessage
//    (
//        1,
//        3.f,
//        FColor::Green,
//        TEXT("Teleport Inactive")
//    );*/
//	bTeleportIsActive = false;
//}
//


