// Fill out your copyright notice in the Description page of Project Settings.


#include "PassByTriggerBox.h"

// Sets default values for this component's properties
UPassByTriggerBox::UPassByTriggerBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	TriggerBox->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	
}


// Called when the game starts
void UPassByTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UPassByTriggerBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

