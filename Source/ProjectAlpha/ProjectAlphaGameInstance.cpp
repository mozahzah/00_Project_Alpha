// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAlphaGameInstance.h"
#include "Crossair.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "LobbyMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"



 UProjectAlphaGameInstance::UProjectAlphaGameInstance(const FObjectInitializer & ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<UUserWidget> CrossairBp (TEXT("/Game/UI/BluePrints/WBP_Crossair"));
    CrossairClass = CrossairBp.Class;

    static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBp (TEXT("/Game/UI/BluePrints/WBP_MainMenu"));
    MainMenuClass = MainMenuBp.Class;

    static ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBp (TEXT("/Game/UI/BluePrints/WBP_InGameMenu"));
    InGameMenuClass = InGameMenuBp.Class;

    static ConstructorHelpers::FClassFinder<UUserWidget> LobbyMenuBp (TEXT("/Game/UI/BluePrints/WBP_LobbyMenu"));
    LobbyMenuClass = LobbyMenuBp.Class;

    
}

void UProjectAlphaGameInstance::Init()
{
    Super::Init();
}


void UProjectAlphaGameInstance::AddReticle()
{
    FInputModeGameOnly GameOnly;
    GetWorld()->GetFirstPlayerController()->SetInputMode(GameOnly);
    auto Crossair = CreateWidget<UCrossair>(this, CrossairClass);
    Crossair->AddToViewport();
}

void UProjectAlphaGameInstance::LoadMainMenu()
{
     MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
     MainMenu->AddToViewport();
     FInputModeUIOnly UIOnly;
     GetWorld()->GetFirstPlayerController()->SetInputMode(UIOnly);
     GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void UProjectAlphaGameInstance::LoadInGameMenu()
 {
     InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
     InGameMenu->AddToViewport();
     FInputModeGameAndUI UIOnly;
     GetWorld()->GetFirstPlayerController()->SetInputMode(UIOnly);
     GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
     isInMenu = true;
 }

void UProjectAlphaGameInstance::UnLoadInGameMenu()
 {
     if (!ensure(InGameMenu)) return;    
     InGameMenu->RemoveFromViewport();
     FInputModeGameOnly GameOnly;
     GetWorld()->GetFirstPlayerController()->SetInputMode(GameOnly);
     GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
     isInMenu = false;
 }

void UProjectAlphaGameInstance::LoadLobbyMenu()
{
     MainMenu->RemoveFromViewport();
     LobbyMenu = CreateWidget<ULobbyMenu>(this, LobbyMenuClass);
     LobbyMenu->AddToViewport();
     FInputModeUIOnly UIOnly;
     GetWorld()->GetFirstPlayerController()->SetInputMode(UIOnly);
     GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}




