// Fill out your copyright notice in the Description page of Project Settings.

#include "LevitatingActor.h"

#include "Particles/ParticleSystemComponent.h"

ALevitatingActor::ALevitatingActor()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    SetMobility(EComponentMobility::Movable);

    if (GetStaticMeshComponent())
    {
        GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ALevitatingActor::OnHit);
    }
}

void ALevitatingActor::Destroyed()
{
    if (GetStaticMeshComponent())
    {
        GetStaticMeshComponent()->OnComponentHit.RemoveDynamic(this, &ALevitatingActor::OnHit);
    }

    Super::Destroyed();
}

void ALevitatingActor::RequestLevitation(const AActor* RequesteeActor)
{
    bool bSuccess = true;
    if (RequesteeActor)
    {
        SourceActor = RequesteeActor;
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

    MaxLevitationHeight = FMath::FRandRange(MinRandomLevitationHeight, MaxRandomLevitationHeight);
    LevitationSpeed = FMath::FRandRange(MinRandomLevitationSpeed, MaxRandomLevitationSpeed);
    SpringStrenght = FMath::FRandRange(MinRandomSpringStrenght, MaxRandomSpringStrenght);

    CurrentLevitationHeight = 0.0f;
    bHasReachedMaxHeight = false;
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
    if (SourceActor.IsValid())
    {
        const FVector SourceActorLocation = SourceActor->GetActorLocation();
        FVector CurrentLocation = GetActorLocation();

        if (!bHasReachedMaxHeight)
        {
            CurrentLevitationHeight += LevitationSpeed * DeltaSeconds;
            if (CurrentLevitationHeight > MaxLevitationHeight)
            {
                bHasReachedMaxHeight = true;
            }
        }
        else
        {
            const float SinWave = (FMath::Sin((GetWorld()->GetTimeSeconds())));
            CurrentLevitationHeight += SinWave / (FMath::IsNearlyZero(FloatingMotionRange) ? 1.0f : FloatingMotionRange);
        }

        CurrentLocation.X = FMath::FInterpTo(CurrentLocation.X, SourceActorLocation.X + CachedVectorFromSource.X, DeltaSeconds, SpringStrenght);
        CurrentLocation.Y = FMath::FInterpTo(CurrentLocation.Y, SourceActorLocation.Y + CachedVectorFromSource.Y, DeltaSeconds, SpringStrenght);
        CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, SourceActorLocation.Z + CachedVectorFromSource.Z + CurrentLevitationHeight, DeltaSeconds, SpringStrenght);

        SetActorLocation(CurrentLocation);
        SetActorRotation(GetActorRotation() + FRotator(FMath::FRandRange(1, 10) * DeltaSeconds));
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
}
