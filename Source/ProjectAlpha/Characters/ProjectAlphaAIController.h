// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "ProjectAlphaAIController.generated.h"

class AProjectAlphaEnemyCharacter;

UCLASS()
class PROJECTALPHA_API AProjectAlphaAIController : public AAIController
{
	GENERATED_BODY()

protected:
	void Tick(float DeltaSeconds) override;
	void OnPossess(APawn* InPawn) override;

private:
	void PatrolArea(float DeltaSeconds);

private:
	TWeakObjectPtr<AProjectAlphaEnemyCharacter> EnemyCharacter;
	float Timer;
};