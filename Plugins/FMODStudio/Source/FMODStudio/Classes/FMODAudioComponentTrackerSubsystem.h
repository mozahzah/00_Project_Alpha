// BEGIN CHANGE

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "FMODAudioComponentTrackerSubsystem.generated.h"

class UFMODAudioComponent;

UCLASS()
class FMODSTUDIO_API UFMODAudioComponentTrackerSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	void Deinitialize() override;
	TStatId GetStatId() const override { return TStatId(); };

public:
	TArray<TWeakObjectPtr<UFMODAudioComponent>> GetFMODAudioComponents() { return FMODAudioComponents; }
	void AddFMODAudioComponent(UFMODAudioComponent* FMODAudioComponent);
	void RemoveFMODAudioComponent(UFMODAudioComponent* FMODAudioComponent);

private:
	TArray<TWeakObjectPtr<UFMODAudioComponent>> FMODAudioComponents;
};
// END CHANGE