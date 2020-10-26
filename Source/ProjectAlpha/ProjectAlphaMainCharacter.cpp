// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAlphaMainCharacter.h"
#include "AkComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "AkGameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "CollisionShape.h"
#include "AkGameObject.h"
#include "Camera/PlayerCameraManager.h"
#include "ProjectAlphaEnemyCharacter.h"
#include "Engine/StaticMeshActor.h"
#include "AkGameplayTypes.h"
#include "AkAcousticPortal.h"
#include "PreSmokeActor.h"
#include "GameFramework/CharacterMovementComponent.h"


AProjectAlphaMainCharacter::AProjectAlphaMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = 100;

	
}



void AProjectAlphaMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->HideBoneByName(FName("hair_strand1_01"), EPhysBodyOp::PBO_None);
	GetMesh()->HideBoneByName(FName("hair_strand2_01"), EPhysBodyOp::PBO_None);
	GetMesh()->HideBoneByName(FName("teddy_bear_root"), EPhysBodyOp::PBO_None);
	FActorSpawnParameters SpawnParams;
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("FX_Hand_L1"));
	Weapon->SetOwner(this);

	
	UGameplayStatics::GetPlayerController
	(GetWorld(), 0)->SetAudioListenerOverride(GetMesh(),
	FVector(0.000002, -3.857092, 159.559235), FRotator(0, 90, 0));
	
	
	AkMainComponent = FindComponentByClass<UAkComponent>();

	
	auto MainListener = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->FindComponentByClass<UAkComponent>();
	if (MainListener) {
		UE_LOG(LogTemp, Warning, TEXT("Listener Found, ID: %d"), MainListener->GetAkGameObjectID());
	}
	
	MainListener->SetRTPCValue(nullptr, 0, 0, TEXT("LowPass"));

	
	
	//AkGameObjectID MY_DEFAULT_LISTENER = CharacterAkGameObject->GetAkGameObjectID();

	




	//if (AK::SoundEngine::SetDefaultListeners(&MY_DEFAULT_LISTENER, 1) != AK_Success) 
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Failed to Make Listner"));
	//}
	//else 
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Success to  Make Listner"));
	//}
	
}

void AProjectAlphaMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	GetSurfaceMaterial();
	GetFocusPoint();

	float Speed;
	FVector Direction;
	GetCharacterMovement()->Velocity.ToDirectionAndLength(Direction,Speed);
	if (Speed > 300)
	{
		GetCharacterMovement()->MaxAcceleration = 10000;
	}
	else
	{
		GetCharacterMovement()->MaxAcceleration = 700;
	}
	

	
}

void AProjectAlphaMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AProjectAlphaMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AProjectAlphaMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AProjectAlphaMainCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("LookRight"), this, &AProjectAlphaMainCharacter::LookRight);
	PlayerInputComponent->BindAxis(FName("LookRight"), this, &AProjectAlphaMainCharacter::LookRight);
	PlayerInputComponent->BindAction(FName("Sprint"), EInputEvent::IE_Pressed, this, &AProjectAlphaMainCharacter::Sprint);
	PlayerInputComponent->BindAction(FName("Sprint"), EInputEvent::IE_Released, this, &AProjectAlphaMainCharacter::NotSprint);
	PlayerInputComponent->BindAction(FName("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("Snap"), EInputEvent::IE_Pressed, this, &AProjectAlphaMainCharacter::SnapFinger);
	
}

void AProjectAlphaMainCharacter::SnapFinger() 
{
	const FOnAkPostEventCallback PostEventCallback;
	const FString EventName;
	PlayingId = AkMainComponent->PostAkEvent(FingerSnapEvent, 0, PostEventCallback, EventName);
}

void AProjectAlphaMainCharacter::Sprint()
{
	bIsSprinting = true;
}

void AProjectAlphaMainCharacter::NotSprint()
{
	bIsSprinting = false;
}


void AProjectAlphaMainCharacter::MoveForward(float AxisValue)
{
	if (AxisValue == 1)
	{
		bIsMovingFwd = true;
	}
	if (AxisValue == -1)
	{
		bIsMovingBwd = true;
	}
	if (AxisValue == 0)
	{
		bIsMovingFwd = false;
		bIsMovingBwd = false;
	}
	AddMovementInput(GetActorForwardVector()*AxisValue);
}

void AProjectAlphaMainCharacter::MoveRight(float AxisValue)
{
	if (AxisValue == 1)
	{
		bIsMovingLeft = true;
	}
	if (AxisValue == -1)
	{
		bIsMovingRight = true;
	}
	if (AxisValue == 0)
	{
		bIsMovingLeft = false;
		bIsMovingRight = false;
	}
	if (bIsMovingFwd == true)
	{
		AddMovementInput(-GetActorRightVector()*AxisValue/2);
	}
	else
	{
		AddMovementInput(-GetActorRightVector()*AxisValue);
	}
	
}

void AProjectAlphaMainCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(-AxisValue/2);
}

void AProjectAlphaMainCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue/2);
}

void AProjectAlphaMainCharacter::GetFocusPoint()
{
	FVector ViewpointLocation;
	FRotator ViewpointRotation;
	GetController()->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);

	

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 3000,40, FColor::Blue, false, 0,0,5);

	
		

	TArray<FHitResult> OutHits;
	const auto Rotation = FQuat::Identity;
	const FCollisionObjectQueryParams ObjectType = FCollisionObjectQueryParams::AllObjects;
	const auto CollisionShape = FCollisionShape::MakeSphere(3000);
	const FCollisionQueryParams ExtraParams; //FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	
	GetWorld()->SweepMultiByObjectType(OutHits, GetActorLocation(), GetActorLocation(),
		Rotation, ObjectType, CollisionShape, ExtraParams);
	
		for (auto &Hit : OutHits)
		{
			
			if (Cast<AAkAcousticPortal>(Hit.GetActor()))
			{
				
				auto AcousticPortal = Cast<AAkAcousticPortal>(Hit.GetActor());
				DrawDebugLine(GetWorld(), GetActorLocation(), AcousticPortal->GetActorLocation(), FColor::Red, false, 0, 0, 1);

				auto DoorToActor = GetActorLocation() - AcousticPortal->GetActorLocation();
				auto DoorToCenter = FVector(0,-600,-300);

				
				float DeltaAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(DoorToActor.GetSafeNormal(), DoorToCenter.GetSafeNormal())));
				float Distance = FVector::Dist(GetActorLocation(), AcousticPortal->GetActorLocation() + FVector(0,0,-300));
				
				//UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), DeltaAngle);
				//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);
				//UE_LOG(LogTemp, Warning, TEXT("Portal State: %d"), AcousticPortal->GetCurrentState());

				if (Distance > 100) 
				{
					if (DeltaAngle < 53)
					{
						AcousticPortal->OpenPortal();
					}
					if (DeltaAngle > 53)
					{
						AcousticPortal->CurrentState = 0;
						if (AcousticPortal->CurrentState == 0)
						{
							FAkAudioDevice* Dev = FAkAudioDevice::Get();
							if (Dev != nullptr)
							{
								Dev->SetSpatialAudioPortal(AcousticPortal);
							}
						}
					}
				}
				else 
				{
					return;
				}
				


			}
		
			
			if (Cast<AProjectAlphaEnemyCharacter>(Hit.GetActor())) 
			{


				ApplyOcclusionAndObstruction(Hit);

				

				auto ActorsDistance = FVector::Distance(ViewpointLocation,
					Hit.GetActor()->GetActorLocation());

				auto EndDistance = FVector::Distance(ViewpointLocation + ViewpointRotation.Vector() * ActorsDistance, Hit.GetActor()->GetActorLocation());
				auto DRatio = EndDistance / ActorsDistance;
				float Delta = DRatio * 70;


				if (auto AudioComponent = Hit.GetActor()->FindComponentByClass<UAkComponent>())
				{
					//if (bRVAPisOn == false) return;
					//UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());
					//UE_LOG(LogTemp, Warning, TEXT("%f"), Delta);
					const UAkRtpc* RTPCValue = nullptr;

					//AudioComponent->SetOutputBusVolume(2);
					// if Actor Distance < 500 AudioComponent->Lowpass to 30

					//if (Delta > 40) {
						//AudioComponent->SetRTPCValue(RTPCValue, Delta, 0, TEXT("LowPass"));

					//}

				}
			}
		}
}


void AProjectAlphaMainCharacter::ApplyOcclusionAndObstruction(FHitResult Hit) 
{
	DrawDebugLine(GetWorld(), GetActorLocation(), Hit.GetActor()->GetActorLocation(), FColor::Red, false, 0, 0, 1);



	// Raycast to 
	FHitResult WallHit;
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(WallHit, GetActorLocation() + FVector(50, 0, 0), Hit.GetActor()->GetActorLocation(), ECollisionChannel::ECC_Visibility, Params);
	

	if (WallHit.GetActor() != nullptr)
	{
		if (Cast<AStaticMeshActor>(WallHit.GetActor())) 
		{
			if (WallHit.PhysMaterial->SurfaceType.GetValue() == 1)
			{
				auto DeltaDistance = FVector::Distance(GetActorLocation(), WallHit.Location);


				auto AudioComponent = Hit.GetActor()->FindComponentByClass<UAkComponent>();
				const UAkRtpc* RTPCValue = nullptr;
				AudioComponent->SetRTPCValue(RTPCValue, 100, 0, TEXT("Concrete"));
				AudioComponent->SetRTPCValue(RTPCValue, 0, 0, TEXT("Glass"));
				AudioComponent->SetRTPCValue(RTPCValue, 100, 0, TEXT("Dry"));
				
			}

			if (WallHit.PhysMaterial->SurfaceType.GetValue() == 3)
			{
				auto DeltaDistance = FVector::Distance(GetActorLocation(), WallHit.Location);


				auto AudioComponent = Hit.GetActor()->FindComponentByClass<UAkComponent>();
				const UAkRtpc* RTPCValue = nullptr;
				AudioComponent->SetRTPCValue(RTPCValue, 100, 0, TEXT("Glass"));
				AudioComponent->SetRTPCValue(RTPCValue, 0, 0, TEXT("Concrete"));
				AudioComponent->SetRTPCValue(RTPCValue, 100, 0, TEXT("Dry"));

			}
			else 
			{	
				return;
			}
		}
	}
	else
	{
		auto AudioComponent = Hit.GetActor()->FindComponentByClass<UAkComponent>();
		const UAkRtpc* RTPCValue = nullptr;
		AudioComponent->SetRTPCValue(RTPCValue, 0, 0, TEXT("Concrete"));
		AudioComponent->SetRTPCValue(RTPCValue, 0, 0, TEXT("Glass"));
		AudioComponent->SetRTPCValue(RTPCValue, 0, 0, TEXT("Dry"));
	}

}

void AProjectAlphaMainCharacter::GetSurfaceMaterial()
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = true;
	if(GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation()+GetViewRotation().Vector()*50, GetActorLocation()+GetViewRotation().Vector()+FVector(0,0,-1000), ECollisionChannel::ECC_Visibility, Params))
	{
		auto PhysicsMaterial = Hit.PhysMaterial->SurfaceType.GetValue();
		
		if (PhysicsMaterial == 2)
		{
			SurfaceType = FString("Metal");
		}
		else if(PhysicsMaterial == 1)
		{
			SurfaceType = FString("Concrete");
		}
	}
	else
	{
		SurfaceType = FString("Concrete");
	}           
}

void AProjectAlphaMainCharacter::OnFootStepEvent()
{
	const FOnAkPostEventCallback PostEventCallback;
	const FString EventName;
	AkMainComponent->SetSwitch(CurrentSwitch, FString("Material"), SurfaceType);
	PlayingId = AkMainComponent->PostAkEvent(FootStepEvent, 0, PostEventCallback, EventName);
}


float AProjectAlphaMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Health == 0)
	{
		return 0;
	}
	Health = Health - DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Damage Taken on %s by This Amount %f"), *GetOwner()->GetName(), DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f of %s"), Health, *GetOwner()->GetName());
	if (Health == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is DEAD"), *GetOwner()->GetName());
		return 0;
	}
	return DamageAmount;
}


TSubclassOf<APreSmokeActor> AProjectAlphaMainCharacter::GetPreSmoke()
{
	return PreSmokeBlueprint;
}

