// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAlphaAIController.h"


#include "ProjectAlphaEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


void AProjectAlphaAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    StartLocation = GetCharacter()->GetTransform().TransformPosition(Cast<AProjectAlphaEnemyCharacter>(GetCharacter())->FirstTarget);
    EndLocation = GetCharacter()->GetTransform().TransformPosition(Cast<AProjectAlphaEnemyCharacter>(GetCharacter())->SecondTarget);
    TargetLocation = StartLocation;
    CurrentAIState = EAIState::Petrolling;
}




void AProjectAlphaAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    float Distance  =   FVector::Dist(GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
    
   /* if (LineOfSightTo(PlayerPawn))
    {
        CurrentAIState = EAIState::Attacking;
        if (Distance >= 3000)
        {
            StopMovement();
            CurrentAIState = EAIState::Suspicious; 
        }
        else
        {
            if (CheckForCover())
            {
                MoveToCover(CoverLocation);
            }
            else
            {
                Attacking();
            }
            
        }
        LastPlayerLocation = PlayerPawn->GetActorLocation();
        return;
    }*/
    
   // if (CurrentAIState == EAIState::Petrolling)
   // {
       PetrolArea();
       
   // }
    
   /* else if (!LineOfSightTo(PlayerPawn))
    {
        CurrentAIState = Suspicious;
        ClearFocus(EAIFocusPriority::Gameplay);
        if (FVector::Dist(GetPawn()->GetActorLocation(), LastPlayerLocation) <= 100)
        {
            StopMovement();
            if (GetWorld()->GetTimeSeconds() - TimeLastSeen >= 5)
            {
                CurrentAIState = EAIState::Petrolling;
            }
        }
        else
        {
            MoveToLocation(LastPlayerLocation);
            TimeLastSeen = GetWorld()->GetTimeSeconds();
        }
    }*/
}

void AProjectAlphaAIController::Attacking()
{
    GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 400;
    SetFocus(PlayerPawn);
    MoveToActor(PlayerPawn, 200);
    LastPlayerLocation = PlayerPawn->GetActorLocation();
    TimeLastSeen = GetWorld()->GetTimeSeconds();
    // todo if in shoot range shoot()
}

void AProjectAlphaAIController::PetrolArea()
{
    GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 150;
    ClearFocus(EAIFocusPriority::Gameplay);
    CurrentAIState = EAIState::Petrolling;
    
    if (FVector::Distance(TargetLocation, GetPawn()->GetActorLocation()) <= 100)
    {
        FVector Swap = StartLocation;
        StartLocation = EndLocation;
        EndLocation = Swap;
        TargetLocation = StartLocation;
    }
    MoveToLocation(TargetLocation);

}

bool AProjectAlphaAIController::CheckForCover()
{
    FHitResult Hit;
    FCollisionObjectQueryParams CollisionParams;
    const auto CollisionShape = FCollisionShape::MakeSphere(20000);
    TEnumAsByte<EObjectTypeQuery> ObjectToTrace = EObjectTypeQuery::ObjectTypeQuery7;
    TArray<TEnumAsByte<EObjectTypeQuery> > ObjectsToTraceAsByte;
    ObjectsToTraceAsByte.Add(ObjectToTrace);
            
    if(GetWorld()->SweepSingleByObjectType(Hit, GetPawn()->GetActorLocation(), GetPawn()->GetActorLocation(), FQuat(),
                                           FCollisionObjectQueryParams(ObjectsToTraceAsByte), CollisionShape))
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Cover %s"), *Hit.Actor->GetName());
        CoverLocation = Hit.GetActor()->GetActorLocation();
        return true;
    }
    else
    {
        return false;
    }
}

void AProjectAlphaAIController::MoveToCover(FVector CoverLocationToSet)
{
    GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 400;
    MoveToLocation(CoverLocationToSet);
}
