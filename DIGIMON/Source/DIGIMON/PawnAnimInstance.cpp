// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PawnAnimInstance.h"

void UPawnAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		checkf(false, TEXT("UBaisicCharacterAnimInstance를 사용하려면 소유권자가 Pawn이여야 합니다."));
		return;
	}
	else if (!Pawn) { return; }

	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);
}

void UPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent) { return; }

	Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);

	bShoudMove = !FMath::IsNearlyZero(Speed);

	//쓸지 안쓸지 고민중 + fall anim not exist
	//bIsCrouch = MovementComponent->IsCrouching();	
	//bIsFalling = MovementComponent->IsFalling();
}
