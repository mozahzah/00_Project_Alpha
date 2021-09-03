// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool ULobbyMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    Play->OnClicked.AddDynamic(this ,&ULobbyMenu::LoadLevel);
    Quit->OnClicked.AddDynamic(this, &ULobbyMenu::ExitGame);
    return true;
}

void ULobbyMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    Title->SetOpacity(FMath::Clamp(FMath::Abs(FMath::Sin(GetWorld()->GetTimeSeconds())), 0.3f, 1.f));
    
   TimerBlock->SetText(FText::FromString(FDateTime().Now().ToString()));
    
}

void ULobbyMenu::LoadLevel()
{
    GetWorld()->ServerTravel("/Game/Maps/SandBox?listen");
}

void ULobbyMenu::ExitGame()
{
    GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}