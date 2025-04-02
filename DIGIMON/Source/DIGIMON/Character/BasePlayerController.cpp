// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BasePlayerCameraManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
	{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Digimon/Character/IMC_Base.IMC_Base'") };
	check(Asset.Object);

	IMC_BasePlayer = Asset.Object;

	PlayerCameraManagerClass = ABasePlayerCameraManager::StaticClass();

}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SpringArm = GetPawn()->GetComponentByClass<USoftWheelSpringArmComponent>();
	check(SpringArm);
	SpringArm->SetMinMaxTargetArmLength(160.f, 600.f);
	SpringArm->TargetArmLength = 450;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_BasePlayer, 0);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_BasePlayer, TEXT("IA_Move")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Move is disabled"));
	}


	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_BasePlayer, TEXT("IA_LookAround")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_Move is disabled"));
	}

}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StatusComponent = InPawn->GetComponentByClass<UStatusComponent>();
	check(StatusComponent);
}

void ABasePlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	if (StatusComponent && !StatusComponent->CanMove()) { return; }	//StatusComponent를 custom으로

	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator RotationYaw = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(RotationYaw);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(RotationYaw);



	APawn* ControlledPawn = GetPawn();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.X);
	ControlledPawn->AddMovementInput(RightVector, ActionValue.Y);

}

void ABasePlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void ABasePlayerController::UseInventory(const FInputActionValue& InputActionValue)
{
	// add Item InventoryComponent
	//if()


}
