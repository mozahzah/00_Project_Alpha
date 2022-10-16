// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectAlphaEnemyCharacter.h"
#include "AkComponent.h"
#include "AkGameplayStatics.h"
#include "ProjectAlphaMainCharacter.h"
#include "Kismet/GameplayStatics.h"
//#include "ProjectAlpha/Combat/Abilities/Weapon.h"


AProjectAlphaEnemyCharacter::AProjectAlphaEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectAlphaEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AkMainComponent = FindComponentByClass<UAkComponent>();
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(2);

	/*Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	Weapon->SetActorLocation(Weapon->GetActorLocation() + FVector(-10,0,0));
	Weapon->SetOwner(this);*/

	NeutralRotation = GetActorRotation();
}

void AProjectAlphaEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDead)
	{
		GetController()->StopMovement();
		SetActorEnableCollision(false);
	}

	if (const UWorld* const World = GetWorld())
	{
		if (World->GetTimeSeconds() - CurrentTime > 1)
		{
			if (bIsRotated == false)
			{
				SetActorRotation(NeutralRotation + FRotator(0, 2, 0));
				if (World->GetTimeSeconds() - CurrentTime > 2)
				{
					//Weapon->WeaponFire(GetOwner()->GetActorForwardVector().Rotation() + FRotator(2, 0, 0));
					CurrentTime = GetWorld()->GetTimeSeconds();
					bIsRotated = true;
				}
			}
			else
			{
				SetActorRotation(NeutralRotation + FRotator(0, -2, 0));
				if (World->GetTimeSeconds() - CurrentTime > 2)
				{
					//Weapon->WeaponFire(GetOwner()->GetActorForwardVector().Rotation() + FRotator(2, 0, 0));
					CurrentTime = World->GetTimeSeconds();
					bIsRotated = false;
				}
			}
		}
	}
}

float AProjectAlphaEnemyCharacter::GetHealthPercent()
{
	return Health / 100.0f;
}

float AProjectAlphaEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (FMath::IsNearlyZero(Health))
	{
		bIsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("%i"), bIsDead);
		return 0;
	}

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return DamageAmount;
}

void AProjectAlphaEnemyCharacter::OnFootStepEvent()
{
	if (AkMainComponent) 
	{
		AkMainComponent->SetSwitch(CurrentSwitch, FString("Material"), SurfaceType);
		AkMainComponent->PostAkEvent(FootStepEvent, 0, FOnAkPostEventCallback(), FString());
	}
}