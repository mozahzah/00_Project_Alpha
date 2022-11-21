// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"

#include "LevitatingActor.generated.h"

class UAkAudioEvent;
class UAkComponent;

UCLASS()
class PROJECTALPHA_API ALevitatingActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	void RequestLevitation(const AActor* RequesteeActor);
	void ResetActor();
	
protected:
	ALevitatingActor();
	void Tick(float DeltaSeconds) override;
	void Destroyed() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
private:
	void ProcessLevitation(float DeltaSeconds);

private:
	/* Minimum Levitation Height */
	UPROPERTY(EditAnywhere, Category ="Physics", meta = (ClampMin = 0, UIMin = 0))
	float MinRandomLevitationHeight = 60;

	/* Maximum Levitation Height */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 0, UIMin = 0))
	float MaxRandomLevitationHeight = 120;

	/* Minimum Levitation Speed */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 1, UIMin = 1))
	float MinRandomLevitationSpeed = 30;

	/* Maximum Levitation Speed */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 1, UIMin = 1))
	float MaxRandomLevitationSpeed = 60;

	/* Floating Motion Range */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 1, UIMin = 1))
	float FloatingMotionRange = 3;

	/* Minimum SpringStrenght */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 0, UIMin = 0))
	float MinRandomSpringStrenght = 0.1;

	/* Maximum SpringStrenght */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 0, UIMin = 0))
	float MaxRandomSpringStrenght = 3;

private:
	TWeakObjectPtr<const AActor> SourceActor;
	FVector CachedVectorFromSource;

	float CurrentLevitationHeight;
	float MaxLevitationHeight;
	float LevitationSpeed;
	float SpringStrenght;

	bool bIsLevitated = false;
	bool bHasReachedMaxHeight = false;
};