// BEGIN CHANGE

#include "FMODAudioComponentTrackerSubsystem.h"

#include "FMODAudioComponent.h"

void UFMODAudioComponentTrackerSubsystem::Deinitialize()
{
	FMODAudioComponents.Empty();
}

void UFMODAudioComponentTrackerSubsystem::AddFMODAudioComponent(UFMODAudioComponent* FMODAudioComponent)
{
	if (FMODAudioComponent)
	{
		FMODAudioComponent->OnFMODAudioComponentDestroyed.AddUObject(this, &UFMODAudioComponentTrackerSubsystem::RemoveFMODAudioComponent);
		FMODAudioComponents.Add(FMODAudioComponent);
	}
}

void UFMODAudioComponentTrackerSubsystem::RemoveFMODAudioComponent(UFMODAudioComponent* FMODAudioComponent)
{
	FMODAudioComponents.Remove(FMODAudioComponent);
}
// END CHANGE