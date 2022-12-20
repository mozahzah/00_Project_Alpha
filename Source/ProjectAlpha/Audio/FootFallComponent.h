// Copyright 2023 mozahzah. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "FootFallComponent.generated.h"

class UCharacterMovementComponent;
class USkeletalMeshComponent;
class UFMODAudioComponent;
class UFMODEvent;

UENUM()
enum class EFootFallFoot : uint8 
{
	Left,
	Right,
};

UENUM()
enum class EFootStatus : uint8
{
	InAir,
	InFront,
	OnGround,
};

UENUM()
enum class EMovementDirection : uint8
{
	Forward,
	Backward,
};

USTRUCT(BlueprintType)
struct FFootData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (Tooltip = "String Reference of the Heel Socket."))
	FName HeelSocketName = FName("l_heel_footstep_socket");

	UPROPERTY(EditAnywhere, meta = (Tooltip = "String Reference of the Toe Socket."))
	FName ToeSocketName = FName("l_toe_footstep_socket");

	TMap<FName, float> SocketHeight;
	EFootStatus CurrentFootStatus = EFootStatus::OnGround;
	EPhysicalSurface CurrentSurfaceType = EPhysicalSurface::SurfaceType_Default;
	float FootDotProduct = 0.f;
	bool bHasPlayed = false;
};

USTRUCT(BlueprintType)
struct FFootFallComponentData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (Tooltip = "Foot Data Map and Socket Initilization."))
	TMap <EFootFallFoot, FFootData> FootDataMap;

public:
	EMovementDirection CurrentDirection = EMovementDirection::Forward;
	FVector CharacterVelocity = FVector::ZeroVector;
	float CurrentCharacterSpeedRatio = 0.f;
	int32 CurrentFootStepIndex = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTALPHA_API UFootFallComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	const FFootFallComponentData& GetFootFallComponentData() const {return FootFallComponentData;}

private:
	UFootFallComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateMovementDirection();
	bool IsFootInFront(EFootFallFoot Foot);

	FName GetCurrentSocket(EFootFallFoot Foot) const;
	float GetSocketRelativeHeight(const FName& SocketName) const;
	float GetSocketFloorHeight(const FName& SocketName) const;
	bool IsFootDown(EFootFallFoot Foot);

	void UpdateFootFallGeneralData(float DeltaTime);
	void UpdateFootFallFootData(const EFootFallFoot Foot, float DeltaTime);
	void SendFootFallComponentDataToFMOD(const EFootFallFoot Foot, UFMODAudioComponent* FMODAudioComponent) const;

	EPhysicalSurface GetSurfaceMaterial(FVector SocketLocation) const;

	bool ProcessFootStepSound(EFootFallFoot Foot);

private:
	UPROPERTY(EditDefaultsOnly, Category = "FootFall Component|Data")
	FFootFallComponentData FootFallComponentData;

	UPROPERTY(EditDefaultsOnly, Category = "FootFall Component|Data")
	TObjectPtr<UFMODEvent> FootstepAudioEvent;

	UPROPERTY(EditDefaultsOnly, Category = "FootFall Component|Settings", meta = (ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "1000.0"))
	float TraceLength = 60.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "FootFall Component|Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float RefreshInterval = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "FootFall Component|Settings", meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))
	float MinimumHeight = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FootFall Component|Settings", meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))
	float DynamicHeightAdjuster = 4.0f;

	UPROPERTY(EditDefaultsOnly, Category = "FootFall Component|Settings", meta = (ClampMin = "0.0", ClampMax = "25.0", UIMin = "0.0", UIMax = "25.0"))
	float MinimumSpeed = 10.0f;

private:
	UPROPERTY(Transient)
	TObjectPtr<UFMODAudioComponent> LeftFootFMODAudioComponent;

	UPROPERTY(Transient)
	TObjectPtr<UFMODAudioComponent> RightFootFMODAudioComponent;

private:
	float RefreshIntervalTimer;
	float EnemyAlertTimer;

	TWeakObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	TWeakObjectPtr<USkeletalMeshComponent> SkeletelMeshComponent;	
};