// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AdvanceFloatingPawnMovement.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API UAdvanceFloatingPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
	
public:
	UAdvanceFloatingPawnMovement();

	/** Returns how far to rotate character during the time interval DeltaTime. */
	virtual FRotator GetDeltaRotation(float DeltaTime) const;

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PhysicsRotation(float DeltaTime);

	virtual bool CheckFalling(float DeltaTime);
	virtual bool IsFalling() const override;
	virtual bool IsMovingOnGround() const override;
	virtual void MoveToLocation(FVector NewTargetLocation, float Speed);
	virtual void MoveToLocation(float fTime, float Speed);

	virtual FVector NewFallVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const;
	virtual FRotator ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const;
public:
	virtual void LaunchPawn(FVector LaunchVelocity, bool bXYOverride, bool bZOverride);
	virtual FVector LaunchVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const;
protected:
	UPROPERTY()
	FVector AccelerationAdvance;
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	uint8 bOrientRotationToMovement : 1;
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	FRotator RotationRate;
public:
	bool bFalling = false;
	UPROPERTY(EditAnywhere)
	float FallingDeltaTime = 0.f;	//체크
	FVector TargetLocation = FVector(0, 0, 0);
	float fSpeed = 0;
	float MovingTime = 0;
	bool bIsMoving = false;
	bool bDetectLocation = false;
	bool bLaunch = false;
	FVector LaunchVel = FVector(0, 0, 0);
};
