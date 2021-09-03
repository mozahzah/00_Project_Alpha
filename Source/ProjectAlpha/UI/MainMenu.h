// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Enter;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;

	UFUNCTION()
	void LoadLobby();

	
};
