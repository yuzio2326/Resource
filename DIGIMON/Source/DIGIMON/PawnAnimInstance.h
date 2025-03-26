// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PawnAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API UPawnAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void SetAimRotation(const FRotator& NewAimRotation) { AimRotation = NewAimRotation; }
	const FRotator& GetAimRotation() { return AimRotation; }



protected:
	UPROPERTY()
	class UPawnMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly)
	double Speed = 0.0;

	UPROPERTY(BlueprintReadOnly)
	bool bShoudMove = false;

	/*쓸지 안쓸지 고민중 + fall anim not exist */
	//UPROPERTY(BlueprintReadOnly)
	//bool bIsCrouch = false;
	//UPROPERTY(BlueprintReadOnly)
	//bool bIsFalling = false;

	UPROPERTY(BlueprintReadOnly)
	FRotator AimRotation;



	
};
