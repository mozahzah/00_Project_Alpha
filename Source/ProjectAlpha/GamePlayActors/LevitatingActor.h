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
	UPROPERTY(Transient)
	TObjectPtr<UAkComponent> AkComponent;

	/* Minimum Levitation Height */
	UPROPERTY(EditAnywhere, Category ="Physics", meta = (ClampMin = 0, UIMin = 0))
	float MinRandomLevitationHeight = 20;

	/* Maximum Levitation Height */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 0, UIMin = 0))
	float MaxRandomLevitationHeight = 100;

	/* Minimum Levitation Speed */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 1, UIMin = 1))
	float MinRandomLevitationSpeed = 1;

	/* Maximum Levitation Speed */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 1, UIMin = 1))
	float MaxRandomLevitationSpeed = 10;

	/* Floating Motion Range */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 1, UIMin = 1))
	float FloatingMotionRange = 3;

	/* Minimum SpringStrenght */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 0, UIMin = 0))
	float MinRandomSpringStrenght = 0.1;

	/* Maximum SpringStrenght */
	UPROPERTY(EditAnywhere, Category = "Physics", meta = (ClampMin = 0, UIMin = 0))
	float MaxRandomSpringStrenght = 3;

	/* The sound event to play when the object hits the ground */
	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<UAkAudioEvent> OnHitAudioEvent;

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