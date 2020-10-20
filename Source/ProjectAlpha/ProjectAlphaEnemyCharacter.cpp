// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAlphaEnemyCharacter.h"
#include "AkComponent.h"
#include "AkGameplayStatics.h"
#include "ProjectAlphaMainCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectAlphaEnemyCharacter::AProjectAlphaEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	

}

// Called when the game starts or when spawned
void AProjectAlphaEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AkMainComponent = FindComponentByClass<UAkComponent>();
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(2);
	
}

// Called every frame
void AProjectAlphaEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDead == true) {
		GetController()->StopMovement();
		SetActorEnableCollision(false);
	}

}


float AProjectAlphaEnemyCharacter::GetHealthPercent()
{
	return (float)Health / 100;
}


float AProjectAlphaEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Health == 0)
	{
		return 0;
	}
	Health = Health - DamageAmount;
	if (Health == 0)
	{
		bIsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("%i"), bIsDead);

		return 0;
	}
	return DamageAmount;
}


void AProjectAlphaEnemyCharacter::OnFootStepEvent() {



	const FOnAkPostEventCallback PostEventCallback;
	const FString EventName;
	AkMainComponent->SetSwitch(CurrentSwitch, FString("Material"), SurfaceType);
	auto PlayingId = AkMainComponent->PostAkEvent(FootStepEvent, 0, PostEventCallback, EventName);
}