// Fill out your copyright notice in the Description page of Project Settings.

#include "LevitatingActor.h"

#include "AkGameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#include "AkComponent.h"

ALevitatingActor::ALevitatingActor()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    AkComponent = CreateDefaultSubobject<UAkComponent>(FName(TEXT("LevitatingActor_AkComponent")), true);
    if (AkComponent)
    {
        AkComponent->SetupAttachment(GetRootComponent());
    }
}

void ALevitatingActor::BeginPlay()
{
    Super::BeginPlay();

    if (GetStaticMeshComponent())
    {
        GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ALevitatingActor::OnHit);
    }
}

void ALevitatingActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (AkComponent)
    {
        AkComponent->DestroyComponent();
        AkComponent = nullptr;
    }

    if (GetStaticMeshComponent())
    {
        GetStaticMeshComponent()->OnComponentHit.RemoveDynamic(this, &ALevitatingActor::OnHit);
    }
}

void ALevitatingActor::LevitationRequested(const AActor* Actor)
{
    bool bSuccess = true;
    if (Actor)
    {
        SourceActor = Actor;
        CachedVectorFromSource = GetActorLocation() - SourceActor->GetActorLocation();
    }
    else
    {
        bSuccess = false;
    }

    if (GetStaticMeshComponent())
    {
        GetStaticMeshComponent()->SetEnableGravity(false);
        GetStaticMeshComponent()->SetSimulatePhysics(false);
    }

    bIsLevitated = bSuccess;
}

void ALevitatingActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bIsLevitated)
    {
        ProcessLevitation(DeltaSeconds);
    }
}

void ALevitatingActor::ProcessLevitation(float DeltaSeconds)
{
    //const float Sin = (FMath::Sin((GetWorld()->GetTimeSeconds())));
    if (SourceActor.IsValid())
    {
        const FVector SourceActorLocation = SourceActor->GetActorLocation();
        FVector CurrentLocation;

        const float Rand = FMath::FRandRange(10, 100);

        CurrentLocation.X = FMath::FInterpTo(CurrentLocation.X, SourceActorLocation.X + Rand, DeltaSeconds, Rand);
        CurrentLocation.Y = FMath::FInterpTo(CurrentLocation.Y, SourceActorLocation.Y + Rand, DeltaSeconds, Rand);
        CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, SourceActorLocation.Z + Rand, DeltaSeconds, Rand) + FMath::FRandRange(50, 100) * DeltaSeconds;
        CurrentLocation += CachedVectorFromSource;

        SetActorLocation(CurrentLocation);
        SetActorRotation(FRotator(FMath::Rand()));
    }
}

void ALevitatingActor::ResetActor()
{
    if (GetStaticMeshComponent())
    {
        GetStaticMeshComponent()->SetEnableGravity(true);
        GetStaticMeshComponent()->SetSimulatePhysics(true);
    }

    SourceActor.Reset();
    bIsLevitated = false;
}

void ALevitatingActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // DO ONCE
    if (AkComponent)
    {
        //AkComponent->PostAkEvent(OnHitAudioEvent, ...);
    }
}
