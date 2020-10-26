// Fill out your copyright notice in the Description page of Project Settings.


#include "Crossair.h"
#include "Components/TextBlock.h"

bool UCrossair::Initialize()
{
    bool Success = Super::Initialize();
    if(!Success) return false;
    return true;
}

void UCrossair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    Title->SetOpacity(FMath::Clamp(FMath::Sin(GetWorld()->GetTimeSeconds()), 0.8f, 1.f));
}
