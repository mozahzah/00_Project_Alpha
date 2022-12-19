// Copyright 2023 mozahzah. All Rights Reserved.

#include "ProjectAlphaAIController.h"

#include "ProjectAlpha/Characters/ProjectAlphaEnemyCharacter.h"

namespace AIControllerUtil
{
	static constexpr float DistanceBuffer = 100.0f;
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

	Super::OnPossess(InPawn);
}

void AProjectAlphaAIController::PatrolArea(float DeltaSeconds)
{
	if (EnemyCharacter.IsValid())
	{
		if (!EnemyCharacter->GetPatrolNodes().IsEmpty() && EnemyCharacter->CurrentPatrolNodeIndex < EnemyCharacter->GetPatrolNodes().Num())
		{
			const FVector CharacterLocation = EnemyCharacter->GetActorLocation();
			const float DistanceToNode = FVector::DistSquared2D(CharacterLocation, EnemyCharacter->GetPatrolNodes()[EnemyCharacter->CurrentPatrolNodeIndex]);
			if (DistanceToNode < FMath::Square(AIControllerUtil::DistanceBuffer))
			{
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
				const FVector Location = EnemyCharacter->GetPatrolNodes()[EnemyCharacter->CurrentPatrolNodeIndex];
				EPathFollowingRequestResult::Type MoveResult = MoveToLocation(Location);
			}
		}
	}
}