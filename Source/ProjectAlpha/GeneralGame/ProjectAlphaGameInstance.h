// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "ProjectAlphaGameInstance.generated.h"

class UInGameMenu;
class UCrossair;
class UMainMenu;
class ULobbyMenu;
class UUserWidget;

UCLASS()
class PROJECTALPHA_API UProjectAlphaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	virtual void Init() override;
	TSubclassOf<UUserWidget> CrossairClass;
	TSubclassOf<UUserWidget> MainMenuClass;
	TSubclassOf<UUserWidget> InGameMenuClass;
	TSubclassOf<UUserWidget> LobbyMenuClass;

	
public:
	
	UProjectAlphaGameInstance(const FObjectInitializer & ObjectInitializer);
	

	UMainMenu* MainMenu;
	UInGameMenu* InGameMenu;
	ULobbyMenu* LobbyMenu;
	
	UFUNCTION(BlueprintCallable)
	void AddReticle();

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
    void LoadLobbyMenu();	

	UFUNCTION(BlueprintCallable)
    void LoadInGameMenu();

	UFUNCTION(BlueprintCallable)
    void UnLoadInGameMenu();

	UPROPERTY(BlueprintReadOnly)
	bool isInMenu;


};
