// COPYRIGHT

#include "ProjectAlpha/Combat/Abilities/Ability.h"

void UAbility::Initialize(const AActor*& OwnerActor)
{
	if (OwnerActor) 
	{
		this->OwnerActor = OwnerActor;
		OnInitialize();
	}
}
