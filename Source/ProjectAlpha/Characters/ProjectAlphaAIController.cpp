// Copyright 2023 mozahzah. All Rights Reserved.

#include "ProjectAlphaAIController.h"

#include "ProjectAlpha/Characters/ProjectAlphaEnemyCharacter.h"

namespace AIControllerUtil
{
	static constexpr float DistanceBuffer = 5.f;
}

void AProjectAlphaAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
	if (EnemyCharacter.Get())
	{
		switch (EnemyCharacter->GetCurrentAIState())
		{
			case EAIState::Patrolling:
			{
				PatrolArea(DeltaSeconds);
				break;
			}
			case EAIState::Suspicious:
			{
				// TODO
				break;
			}
			case EAIState::Attacking:
			{
				// TODO
				break;
			}
		}
	}
}

void AProjectAlphaAIController::OnPossess(APawn* InPawn)
{
	if (AProjectAlphaEnemyCharacter* const EnemyChar = Cast<AProjectAlphaEnemyCharacter>(InPawn)) 
	{
		EnemyCharacter = EnemyChar;
	}
}

void AProjectAlphaAIController::PatrolArea(float DeltaSeconds)
{
	if (EnemyCharacter.IsValid())
	{
		if (!EnemyCharacter->GetPatrolNodes().IsEmpty() && EnemyCharacter->CurrentPatrolNodeIndex < EnemyCharacter->GetPatrolNodes().Num())
		{
			const FVector CharacterLocation = GetCharacter() ? GetCharacter()->GetActorLocation() : FVector::ZeroVector;
			if (FVector::Dist(CharacterLocation, EnemyCharacter->GetPatrolNodes()[EnemyCharacter->CurrentPatrolNodeIndex]) < AIControllerUtil::DistanceBuffer)
			{
				bIsMoving = false;
				if (Timer > EnemyCharacter->GetTimeAtPatrolNode())
				{
					EnemyCharacter->CurrentPatrolNodeIndex = (EnemyCharacter->CurrentPatrolNodeIndex + 1) % EnemyCharacter->GetPatrolNodes().Num();
					Timer = 0.0f;
				}
				else
				{
					Timer += DeltaSeconds;
				}
			}
			else
			{
				if (!bIsMoving) 
				{
					const FVector Location = EnemyCharacter->GetPatrolNodes()[EnemyCharacter->CurrentPatrolNodeIndex];
					EPathFollowingRequestResult::Type MoveResult = MoveToLocation(Location);
					if (MoveResult == EPathFollowingRequestResult::RequestSuccessful) 
					{
						bIsMoving = true;
					}
				}
			}
		}
	}
}