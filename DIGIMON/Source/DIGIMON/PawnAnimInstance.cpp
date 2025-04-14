#include "PawnAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/BasePlayerController.h"

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

	// TODO:: ADD Movement 
	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);
}

void UPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent) { return; }

	Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);

	bShoudMove = !FMath::IsNearlyZero(Speed);

	APawn* Pawn = TryGetPawnOwner();
	FRotator Rotation = Pawn->GetActorRotation();
	Direction = CalculateDirection(MovementComponent->Velocity, Rotation);

	//Pawn->GetController();
	ABasePlayerController* OwnPlayerController = Cast<ABasePlayerController>(Pawn->GetController());
	if (OwnPlayerController)
	{
		ZoomAnim = OwnPlayerController->IsZoom;
	}
	// 
	// 
	//Updating Rotation
	//Direction = AimRotation.Yaw;
	//if (Direction > 180.0) { Direction -= 360.0; }
	//else if (Direction < -180.0) { Direction += 360.0; }


	//쓸지 안쓸지 고민중 + fall anim not exist
	//bIsCrouch = MovementComponent->IsCrouching();	
	//bIsFalling = MovementComponent->IsFalling();
}
