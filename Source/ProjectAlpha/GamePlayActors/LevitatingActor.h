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
	void LevitationRequested(const AActor* SourceActor);
	void ResetActor();
	
protected:
	ALevitatingActor();
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaSeconds);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
private:
	void ProcessLevitation(float DeltaSeconds);

private:
	UPROPERTY(Transient)
	TObjectPtr<UAkComponent> AkComponent;

	/* The sound event to play when the object hits the ground */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAkAudioEvent> OnHitAudioEvent;

private:
	TWeakObjectPtr<const AActor> SourceActor;
	FVector CachedVectorFromSource;
	bool bIsLevitated = false;

};