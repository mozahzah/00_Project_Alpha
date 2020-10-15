// Fill out your copyright notice in the Description page of Project Settings.


#include "TelekineticObjects.h"

#include "AkGameplayStatics.h"
#include "ProjectAlphaEnemyCharacter.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATelekineticObjects::ATelekineticObjects()
{
    
}

void ATelekineticObjects::BeginPlay()
{
    Super::BeginPlay();
    GetParticleSystem();
    //GetStaticMeshComponent()->SetNotifyRigidBodyCollision(false);
    //GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ATelekineticObjects::OnHit);

    MaxHeight = FMath::FRandRange(75, 170);
    ZValue = FMath::FRandRange(-10, 10);
    RotationDelta = FMath::FRandRange(-0.1,0.1);
}

void ATelekineticObjects::SetObjectLocation(FVector CharacterLocation, FKineticObjectData ObjectData, float DeltaTime)
{
    LevitationHeight = FMath::FInterpTo(LevitationHeight, MaxHeight , DeltaTime, 2.f);
    float Delta = (FMath::Sin((GetWorld()->GetTimeSeconds())*2));
    
    if (bIsLevitated == false)
    {
        CurrentLocation = CharacterLocation;
    }

    CurrentLocation.X = FMath::FInterpTo(CurrentLocation.X, CharacterLocation.X, DeltaTime*0.5, 2.f);
    CurrentLocation.Y = FMath::FInterpTo(CurrentLocation.Y, CharacterLocation.Y, DeltaTime*0.5, 2.f);
    CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, CharacterLocation.Z,DeltaTime*0.5, 2.f);

    auto Location = CurrentLocation + ObjectData.Direction.Vector() * ObjectData.Distance;
    Location.Z += Delta*ZValue + LevitationHeight;
    SetActorLocation((Location)  , false, nullptr,ETeleportType::TeleportPhysics);
    GetStaticMeshComponent()->AddLocalRotation(FRotator(RotationDelta,RotationDelta,RotationDelta));
}

void ATelekineticObjects::ResetObject()
{
    GetStaticMeshComponent()->SetEnableGravity(true);
    GetStaticMeshComponent()->SetSimulatePhysics(true);
    LevitationHeight = 0.f;
    GetStaticMeshComponent()->SetPhysicsLinearVelocity(FVector(0));
    GetStaticMeshComponent()->SetPhysicsAngularVelocityInDegrees(FVector(0));
    DeactivateParticleSystem();
    bIsLevitated = false;
    GetStaticMeshComponent()->SetNotifyRigidBodyCollision(true);
    MaxHeight = FMath::FRandRange(75, 170);
    ZValue = FMath::FRandRange(-10, 10);
    RotationDelta = FMath::FRandRange(-0.1,0.1);
}

void ATelekineticObjects::ActivateParticleSystem()
{
    TelekineticObjectParticleFx->Activate();
}

void ATelekineticObjects::DeactivateParticleSystem()
{
    TelekineticObjectParticleFx->Deactivate();
}

void ATelekineticObjects::GetParticleSystem()
{
   TelekineticObjectParticleFx = this->FindComponentByClass<UParticleSystemComponent>();
   if (!ensure(TelekineticObjectParticleFx))
   {
       UE_LOG(LogTemp, Warning, TEXT("Particle System Not Found"));
   }
}

//void ATelekineticObjects::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//    FPointDamageEvent DamageEvent (10, Hit, FVector(0), nullptr);
//    //if (!ensure(OtherActor)) return;
//    
//    {  
//        AProjectAlphaEnemyCharacter* Enemy = Cast<AProjectAlphaEnemyCharacter>(OtherActor);
//        //if (!ensure(Enemy)) return;
//        Enemy->TakeDamage(10, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
//        
//    }
//
//    
//    UE_LOG(LogTemp, Warning, TEXT("HIT!!!!"));
//    FOnAkPostEventCallback PostEventCallback;
//    PlayingId = UAkGameplayStatics::PostEvent(AkHitEvent, this, 0, PostEventCallback);
//    GetStaticMeshComponent()->SetNotifyRigidBodyCollision(false);
//}
