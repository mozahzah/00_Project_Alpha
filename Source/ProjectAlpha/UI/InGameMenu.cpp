// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"


#include "ProjectAlpha/ProjectAlphaGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UInGameMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    Settings->OnClicked.AddDynamic(this ,&UInGameMenu::LoadSettings);
    Cancel->OnClicked.AddDynamic(this, &UInGameMenu::UnLoadMainMenu);
    Exit->OnClicked.AddDynamic(this ,&UInGameMenu::ExitGame);
    
    return true;
}

void UInGameMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    Title->SetOpacity(FMath::Clamp(FMath::Abs(FMath::Sin(GetWorld()->GetTimeSeconds())), 0.5f, 1.f));
}


void UInGameMenu::LoadSettings()
{
    return;
}

void UInGameMenu::ExitGame()
{
    GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UInGameMenu::UnLoadMainMenu()
{
    Cast<UProjectAlphaGameInstance>(GetGameInstance())->UnLoadInGameMenu();
}
