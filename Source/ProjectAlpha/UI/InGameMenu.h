// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()

	protected:
	
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	class UButton* Settings;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Cancel;

	UPROPERTY(meta = (BindWidget))
	class UButton* Exit;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;

	UFUNCTION()
    void LoadSettings();

	UFUNCTION()
    void ExitGame();

	UFUNCTION()
	void UnLoadMainMenu();
	
};
