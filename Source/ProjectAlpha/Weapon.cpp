// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"


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

void AWeapon::WeaponFire(FVector Start, FRotator Rotation)
{
	FHitResult Hit;
	FVector End = Start + Rotation.Vector()*1000000;
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_PhysicsBody);
	if (Hit.Actor != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFX, Hit.Location, FRotator(0), FVector(1), true, EPSCPoolMethod::None, true);
		FPointDamageEvent DamageEvent (WeaponDamage, Hit, FVector(0), nullptr);

		AActor* Enemy = Hit.GetActor();
		if (Enemy != nullptr)
		{
			Enemy->TakeDamage(WeaponDamage, DamageEvent, Cast<APawn>(GetOwner())->GetController(), this);
		}
	}

}
