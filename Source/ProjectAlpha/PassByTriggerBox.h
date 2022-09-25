// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PassByTriggerBox.generated.h"

UENUM() enum class EPassByTriggerSide : uint8
{
	left,
	front,
	right,
	back,
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTALPHA_API UPassByTriggerBox : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassByTriggerBox();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere) EPassByTriggerSide side;
	UBoxComponent *TriggerBox;


	
};
