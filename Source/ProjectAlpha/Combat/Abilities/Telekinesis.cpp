
#include "Telekinesis.h"
#include "DrawDebugHelpers.h"
#include "ProjectAlpha/OtherActors/TelekineticObjects.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectAlpha/Characters/ProjectAlphaMainCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "AkComponent.h"
#include "AkGameplayStatics.h"

UTelekinesis::UTelekinesis()
{
	PrimaryComponentTick.bCanEverTick = true;
}

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
bool UTelekinesis::RayCastObjects()
{
	TArray<struct FHitResult> HitResults;
    const auto Rotation = GetOwner()->GetActorRotation().Quaternion();
	const ECollisionChannel TraceChannel = ECollisionChannel::ECC_GameTraceChannel1;
    const auto CollisionShape = FCollisionShape::MakeSphere(Radius);
    const FCollisionQueryParams ExtraParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	
    GetWorld()->SweepMultiByChannel(HitResults,CharacterLocation ,CharacterLocation, Rotation, TraceChannel, CollisionShape, ExtraParams);
	if (HitResults.Num() == 0) return false;
	for (const auto& HitResult : HitResults)
	{
		const auto ActorHit = HitResult.GetActor();
		if (ActorHit)
		{
			if (!ensure(PhysicsHandler)) return false;
			if (!ensure(HitResult.GetComponent())) return false;
			PhysicsHandler->GrabComponentAtLocation(HitResult.GetComponent(), NAME_None, ActorHit->GetActorLocation());
			GrabbedComponents.Add(Cast<ATelekineticObjects>(PhysicsHandler->GrabbedComponent->GetOwner()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Hit"));
			return false;
		}
	}
	if(HitResults.Num() > 0)
	{
		LevitationDelay = GetWorld()->GetTimeSeconds();
		return true;
	}
	else
	{
		return false;
	}
}
void UTelekinesis::LevitateObjects(float DeltaTime)
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
	bTelekinesisIsActive = false;
	MagicLeftHand->Deactivate();
	MagicRightHand->Deactivate();
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