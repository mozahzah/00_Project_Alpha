// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "DynamicAudioPerception.generated.h"

class UFMODAudioComponentTrackerSubsystem;

UCLASS(meta = (BlueprintSpawnableComponent))
class PROJECTALPHA_API UDynamicAudioPerception : public UActorComponent
{
	GENERATED_BODY()

public:
	UDynamicAudioPerception();

protected:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void ProcessDynamicAudioPerception();

private:
	/* Whether to enable this feature or not */
	UPROPERTY(EditDefaultsOnly)
	bool bEnable;

	/* String reference of the FMOD property we want to manipulate */
	UPROPERTY(EditDefaultsOnly)
	FName ParameterName;

private:
	TWeakObjectPtr<const APlayerController> PlayerController;
	TWeakObjectPtr<const UFMODAudioComponentTrackerSubsystem> FMODAudioComponentTrackerSubsystem;

};