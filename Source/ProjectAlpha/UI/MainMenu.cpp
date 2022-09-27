// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "ProjectAlpha/GeneralGame/ProjectAlphaGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    Enter->OnClicked.AddDynamic(this ,&UMainMenu::LoadLobby);

    
    return true;
}

void UMainMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    Title->SetOpacity(FMath::Clamp(FMath::Abs(FMath::Sin(GetWorld()->GetTimeSeconds())), 0.3f, 1.f));
    
}


void UMainMenu::LoadLobby()
{
    Cast<UProjectAlphaGameInstance>(GetGameInstance())->LoadLobbyMenu();
}


