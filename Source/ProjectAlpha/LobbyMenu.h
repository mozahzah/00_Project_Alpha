// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API ULobbyMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;
	UPROPERTY(meta = (BindWidget))
	class UButton* Play;

	UPROPERTY(meta = (BindWidget))
	class UButton* Quit;

	
	UFUNCTION()
    void LoadLevel();

	UFUNCTION()
    void ExitGame();
	
};
