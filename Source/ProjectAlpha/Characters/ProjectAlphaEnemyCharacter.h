// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ProjectAlphaEnemyCharacter.generated.h"

class UNavMovementComponent;

UENUM()
enum class EAIState : uint8
{
	Attacking,
	Suspicious,
	Patrolling
};

UCLASS()
class PROJECTALPHA_API AProjectAlphaEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	AProjectAlphaEnemyCharacter();

protected:
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	const TArray<FVector>& GetPatrolNodes() const { return PatrolNodes; }
	float GetTimeAtPatrolNode() const { return TimeAtPatrolNode; }
	EAIState GetCurrentAIState() const { return CurrentAIState; }

public:
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const { return CurrentHealth / MaxHealth; };

private:
	/*Navigation Movement Component*/
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNavMovementComponent> NavMovementComponent;

	/*Starting AI State*/
	UPROPERTY(EditAnywhere)
	EAIState CurrentAIState = EAIState::Patrolling;

	/*Simple AI Patrol Path Nodes*/
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	TArray<FVector> PatrolNodes;

	/*Time to spend when at a patrol node location*/
	UPROPERTY(EditAnywhere)
	float TimeAtPatrolNode = 2.f;

	/*Max Health*/
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	/*Current Health*/
	UPROPERTY(VisibleAnywhere)
    float CurrentHealth = 100.f;

public:
	int16 CurrentPatrolNodeIndex = 0;
};