// COPYRIGHT

#include "ProjectAlpha/Combat/Abilities/Ability.h"

void UAbility::Initialize(AActor* _OwnerActor)
{
	if (_OwnerActor)
	{
		this->OwnerActor = _OwnerActor;
		OnInitialize();
	}
}
