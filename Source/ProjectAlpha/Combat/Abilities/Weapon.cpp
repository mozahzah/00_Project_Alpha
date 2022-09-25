// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::WeaponFire(FRotator Rotation)
{
	TArray<FHitResult> Hits;
	FCollisionQueryParams Params;
	Params.bFindInitialOverlaps = true;
	FVector End = GetActorLocation() + Rotation.Vector()*1000000;
    GetWorld()->LineTraceMultiByChannel(Hits, GetActorLocation(), End, ECollisionChannel::ECC_Visibility, Params);

	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hits.Pop().GetActor()->GetName());

	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFX, Hits.Pop().Location, FRotator(0), FVector(1), true, EPSCPoolMethod::None, true);
	DrawDebugLine(GetWorld(), GetActorLocation(), End, FColor::Red, false, 0.2f);

	//UE_LOG(LogTemp, Warning, TEXT("HIT: %s"), *Hit.Actor->GetName());

	/*if (Hit.Actor != nullptr)
	{
		FPointDamageEvent DamageEvent (WeaponDamage, Hit, FVector(0), nullptr);
		AActor* Enemy = Hit.GetActor();
		if (Enemy != nullptr)
		{
			Enemy->TakeDamage(WeaponDamage, DamageEvent, Cast<APawn>(GetOwner())->GetController(), this);
		}
	}*/
}
