// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"


#include "ProjectAlpha/Combat/Abilities/Teleport.h"
#include "DrawDebugHelpers.h"
#include "ProjectAlpha/Combat/Abilities/Telekinesis.h"
#include "ProjectAlpha/Combat/Abilities/Weapon.h"
#include "ProjectAlpha/Combat/Abilities/SmokeScreen.h"
#include "ProjectAlpha/OtherActors/PreSmokeActor.h"
#include "Components/InputComponent.h"
#include "ProjectAlpha/Characters/ProjectAlphaMainCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	//Getting Ability Components
	if (!ensure(GetWorld()->GetFirstPlayerController())) return;
	Telekinesis = GetOwner()->FindComponentByClass<UTelekinesis>();
	if (!ensure(Telekinesis)) return;
	Teleport = GetOwner()->FindComponentByClass<UTeleport>();
	if (!ensure(Teleport)) return;
	SmokeScreen = GetOwner()->FindComponentByClass<USmokeScreen>();
	if (!ensure(SmokeScreen)) return;
	


	//Input Binding
	GetOwner()->InputComponent->BindAction(FName("ActivateTelekinesis"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateTelekinesis);
	GetOwner()->InputComponent->BindAction(FName("ActivateWeapon"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateWeapon);
	GetOwner()->InputComponent->BindAction(FName("ActivateTeleport"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateTeleport);
	GetOwner()->InputComponent->BindAction(FName("ActivateSmokeScreen"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateSmokeScreen);
	GetOwner()->InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &UCombatComponent::Fire);
	GetOwner()->InputComponent->BindAction(FName("Fire"), EInputEvent::IE_Released, this, &UCombatComponent::StopFire);
	GetOwner()->InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Pressed, this, &UCombatComponent::SecondaryFire);
	GetOwner()->InputComponent->BindAction(FName("SecondaryFire"), EInputEvent::IE_Released, this, &UCombatComponent::StopSecondaryFire);
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AimAt();
	
	if (bAddSmokeMousePressed) 
	{
		SmokeLenght += 1000*DeltaTime;
	}
	if (bMinusSmokeMousePressed) 
	{
		if (SmokeLenght >= 0)
		{	
			SmokeLenght -= 1000*DeltaTime;
		}
	}
	
	if (bCTeleportIsActive)
	{
		if (GetWorld()->GetTimeSeconds() - StartTeleportTimer > 0.2 * 0.5)
		{
			DeactivateTeleport();
		}
	}

	
}


void UCombatComponent::SetReticle()
{
	auto Pawn = Cast<APawn>(GetOwner());
	Pawn->GetController()->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);
}


void UCombatComponent::AimAt()
{
	SetReticle();
	if (CurrentAbility == Abilities::None) return;
	if (CurrentAbility == Abilities::Telekinesis)
	{
		TelekinesisAimAt();
	}
	if (CurrentAbility == Abilities::Teleport)
	{
		TeleportAimAt();
	}

	if (CurrentAbility == Abilities::SmokeScreen) 
	{

		EndLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * SmokeLenght;
		SmokeScreenAimAt();		
	}

	if (CurrentAbility == Abilities::Weapon)
	{
		return;
	}
	else
	{
		return;
	}
	
}

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

void UCombatComponent::TelekinesisAimAt()
{
	FHitResult OutHit;
	FVector Start = ViewpointLocation;
	FVector End = ViewpointLocation + ViewpointRotation.Vector()*1000000;
	if (GetWorld()->LineTraceSingleByChannel(OutHit,Start,End,ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = OutHit.Location;
	}
}


void UCombatComponent::TeleportAimAt()
{
	//Line Tracing 1
	FHitResult OutHit1;
	FVector Start1 = ViewpointLocation ;
	FVector End1 = ViewpointLocation + ViewpointRotation.Vector()*1500;
	if (GetWorld()->LineTraceSingleByChannel(OutHit1,Start1,End1,ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = OutHit1.Location;
	}
	else
	{
		//line Stracing 2
		FHitResult OutHit2;
		FVector Start2 = ViewpointLocation + ViewpointRotation.Vector()*1500;
		FVector End2 = Start2.DownVector*500000;
		if (GetWorld()->LineTraceSingleByChannel(OutHit2,Start2,End2,ECollisionChannel::ECC_Visibility))
		{
			OutHitLocation = OutHit2.Location;
		}
	}
	DrawDebugLine(
	GetWorld(),	OutHitLocation
	, OutHitLocation, FColor::Blue,false, 0, 10, 10);
}


void UCombatComponent::Fire()
{
	if(CurrentAbility == Abilities::Teleport)
	{
		StartTeleportTimer = GetWorld()->GetTimeSeconds();
		bCTeleportIsActive = true;
		OutHitLocation.Z += 100;
		Teleport->Teleport(OutHitLocation);
	} 
	
	if (CurrentAbility == Abilities::Telekinesis)
	{
		auto LastGrabbedIndex = Telekinesis->GrabbedComponents.Num() -1 ;
		if(LastGrabbedIndex < 0) return;
		auto Projectile = (Telekinesis->GrabbedComponents[LastGrabbedIndex]);
		if (!ensure(Projectile)) return;
		Telekinesis->GrabbedComponents.RemoveAt(LastGrabbedIndex);
		Telekinesis->PhysicsHandler->ReleaseComponent();
		Projectile->ResetObject();
		auto OutDirection = (OutHitLocation - Projectile->GetActorLocation()).GetSafeNormal();
		Projectile->GetStaticMeshComponent()->SetPhysicsLinearVelocity( ( OutDirection) * 10000.f);
		if (LastGrabbedIndex == 0) ActivateWeapon();
	}

	if (CurrentAbility == Abilities::Weapon)
	{
		if (!ensure(Weapon)) return;
		Weapon->WeaponFire(ViewpointLocation, ViewpointRotation);
		bCWeaponIsActive = true;
		
	}

	if (CurrentAbility == Abilities::SmokeScreen) 
	{
		bAddSmokeMousePressed = true;
	}
}

void UCombatComponent::StopFire() 
{
	bAddSmokeMousePressed = false;
}

void UCombatComponent::SecondaryFire() 
{
	if (CurrentAbility == Abilities::SmokeScreen)
	{
		bMinusSmokeMousePressed = true;
	}
}

void UCombatComponent::StopSecondaryFire() 
{
	bMinusSmokeMousePressed = false;
}

// ACTIVATION SECTION

void UCombatComponent::ActivateWeapon()
{
	DeactivateTeleport();
	DeactivateTelekinesis();
	DeactivateSmokeScreen();
	Weapon = Cast<AProjectAlphaMainCharacter>(GetOwner())->Weapon;
	CurrentAbility = Abilities::Weapon;
}


void UCombatComponent::ActivateTelekinesis()
{
	DeactivateTeleport();
	DeactivateSmokeScreen();
	Telekinesis->ActivateTelekinesis();
	CurrentAbility = Abilities::Telekinesis;
	bCTelekinesisIsActive = Telekinesis->bTelekinesisIsActive;
	
}

void UCombatComponent::ActivateTeleport()
{
	DeactivateTelekinesis();
	DeactivateSmokeScreen();
	Teleport->ActivateTeleport(OutHitLocation);
	CurrentAbility = Abilities::Teleport;
}

void UCombatComponent::DeactivateTelekinesis()
{
	Telekinesis->DeactivateTelekinesis();
	bCTelekinesisIsActive = false;
}

void UCombatComponent::DeactivateTeleport()
{
	bCTeleportIsActive = false;
	Teleport->DeactivateTeleport();
	CurrentAbility = Abilities::None;
}

void UCombatComponent::ActivateSmokeScreen()
{
	DeactivateTeleport();
	DeactivateTelekinesis();
	CurrentAbility = Abilities::SmokeScreen;
	GetOwner()->InputComponent->RemoveActionBinding(12);
	GetOwner()->InputComponent->BindAction(FName("ActivateSmokeScreen"), EInputEvent::IE_Pressed, this, &UCombatComponent::FireSmoke);
	bCSmokeIsActive = true;
}

void UCombatComponent::DeactivateSmokeScreen() 
{
	bPreSmokeisActive = false;
	if (PreSmoke != nullptr)
	{
		PreSmoke->Destroy();
	}
	bCSmokeIsActive = false;
	bMinusSmokeMousePressed = false;
	bAddSmokeMousePressed = false;
	SmokeLenght = 0;
	CurrentAbility = Abilities::Weapon;
	GetOwner()->InputComponent->RemoveActionBinding(12);
	GetOwner()->InputComponent->BindAction(FName("ActivateSmokeScreen"), EInputEvent::IE_Pressed, this, &UCombatComponent::ActivateSmokeScreen);
}

void UCombatComponent::FireSmoke()
{
	DeactivateSmokeScreen();
	SmokeScreen->ActivateSmokeScreen(EndLocation);
}


