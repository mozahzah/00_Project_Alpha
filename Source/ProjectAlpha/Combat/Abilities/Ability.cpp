// COPYRIGHT

#include "ProjectAlpha/Combat/Abilities/Ability.h"

void UAbility::Initialize(AActor* OwnerActor)
{
	if (OwnerActor) 
	{
		this->OwnerActor = OwnerActor;
		OnInitialize();
	}
}
