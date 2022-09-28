
#include "Telekinesis.h"
#include "DrawDebugHelpers.h"
#include "ProjectAlpha/GamePlayActors/TelekineticObjects.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectAlpha/Characters/ProjectAlphaMainCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "AkComponent.h"
#include "AkGameplayStatics.h"

void UTelekinesis::BeginPlay()
{
	Super::BeginPlay();
	GetPhysicsHandler();
	//GetAudioComponent();
	AkMainComponent = GetOwner()->FindComponentByClass<UAkComponent>();
	MagicLeftHand->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,FName("FX_Hand_R1"));
	MagicRightHand->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,FName("FX_Hand_L1"));
}

void UTelekinesis::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//DrawDebugSphere(
		//GetWorld(),StartLocation, Radius, 10,FColor::Blue,
		//true, 1.f,1, 2.f);

	CharacterLocation = GetOwner()->GetActorLocation();

	if (bTelekinesisIsActive == true)
	{
		LevitateObjects(DeltaTime);	
	}
	
}

void UTelekinesis::ActivateTelekinesis()
{
	if(bTelekinesisIsActive) return;
	if(RayCastObjects())	
	{
		const FOnAkPostEventCallback PostEventCallback;
		const FString EventName;
		PlayingId = AkMainComponent->PostAkEvent(TelekinesisEvent, 0, PostEventCallback, EventName);
		
		bTelekinesisIsActive = true;
		MagicLeftHand->Activate();
		MagicRightHand->Activate();
	}
}


bool UAbility_Telekinesis::RayCastObjects()
{
	if (OwnerActor)
	{
		if (const UWorld* World = OwnerActor->GetWorld())
		{
			const FVector CharacterLocation = OwnerActor->GetActorLocation();
			const FQuat Rotation = GetOwner()->GetActorRotation().Quaternion();
			const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);

			TArray<FHitResult> HitResults;
			if (GetWorld()->SweepMultiByChannel(HitResults, CharacterLocation, CharacterLocation, Rotation, TraceChannel, CollisionShape, FCollisionQueryParams()))
			{
				for (const FHitResult& HitResult : HitResults)
				{
					const ATelekineticObject* TelekineticObject = Cast<ATelekineticObject>(HitResult.GetActor());
					if (TelekineticObject)
					{
						GrabbedTelekineticObjects.Add(TelekineticObject);
						AbilityTimer = World->GetTimeSeconds();
					}
				}
			}
		}
	}
}


void UAbility_Telekinesis::LevitateObjects(const float& DeltaTime)
{
	if (GetWorld()->GetTimeSeconds() - LevitationDelay < 0.5) return;
	for (uint16 i = 0 ; i < GrabbedComponents.Num() ; i++)
	{	
		auto GrabbedObject = GrabbedComponents[i];
		if (GrabbedObject->bIsLevitated == false)	
		{
			GrabbedObject->GetStaticMeshComponent()->SetEnableGravity(false);
			GrabbedObject->GetStaticMeshComponent()->SetSimulatePhysics(false);
			GrabbedObject->KineticObjectData.Direction = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, GrabbedObject->GetActorLocation());
			GrabbedObject->KineticObjectData.Distance = FVector::Dist(GetOwner()->GetActorLocation(), GrabbedObject->GetActorLocation());
			GrabbedObject->ActivateParticleSystem();
			KineticObjectDataArray.Add(GrabbedObject->KineticObjectData);
		}
		GrabbedObject->SetObjectLocation(CharacterLocation, KineticObjectDataArray[i], DeltaTime);
		GrabbedObject->bIsLevitated = true;
	}	
}

void UTelekinesis::DeactivateTelekinesis()
{
	AkMainComponent->Stop();
	ReleaseObjects();
}
void UTelekinesis::ReleaseObjects()
{
	for (uint16 i = 0 ; i < GrabbedComponents.Num(); i++)
	{
		auto GrabbedObject = GrabbedComponents[i];
		PhysicsHandler->ReleaseComponent();
		GrabbedObject->ResetObject();
	}
	KineticObjectDataArray.Empty();
	GrabbedComponents.Empty();
}

void UTelekinesis::GetPhysicsHandler()
{
	if (!ensure(GetOwner())) return;
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!ensure(PhysicsHandler))
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics Handler Not Found"));
	}
}

void UAbility_Telekinesis::OnInitialize()
{

}

void UAbility_Telekinesis::Update(const float& DeltaTime)
{
	LevitateObjects(DeltaTime);
}

bool UAbility_Telekinesis::ProcessLineTrace(const FVector& ViewpointLocation, const FRotator& ViewpointRotation)
{

}

void UAbility_Telekinesis::OnActivate()
{
	RayCastObjects();
}


void UAbility_Telekinesis::OnDeactivate()
{
	ReleaseObjects();
}

void UAbility_Telekinesis::OnFire()
{

}

void UAbility_Telekinesis::DeactivateAbility()
{

}
