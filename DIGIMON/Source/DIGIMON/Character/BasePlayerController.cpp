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
	//Camera Setting
	Super::BeginPlay();
	SpringArm = GetPawn()->GetComponentByClass<USoftWheelSpringArmComponent>();
	UCameraComponent* CameraComponent = GetPawn()->GetComponentByClass<UCameraComponent>();
	
	check(SpringArm);
	//Parter Digimon이 Fallow 한 이후 수치 조정
	SpringArm->SetMinMaxTargetArmLength(100.f, 600.f);
	SpringArm->SetDesiredZoom(400.f);
	SpringArm->TargetArmLength = 400;


	//BeginPlay가 아닌 Zoom 완성시 Zoom 에서 해당 코드를 실행하고 복구하도록 하세요
	//CameraComponent->SetRelativeLocation(FVector(0.0f, 140.0f, 0.0f));
	//Camera->
	//SpringArm->TargetOffset = FVector(0, 120, 100);

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
	if (const UInputAction* InputAction = FUtils::GetInputActionFromName(IMC_BasePlayer, TEXT("IA_MouseRB")))
	{
		// Pressing 활성화시 해당 부분 주석을 풀어주세요
		//EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnZoomIn);
		//EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::OnZoomOut);

		// Pressed 활성화시 해당 부분 주석을 풀어주세요
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnZoomIn);


	}
	else
	{
		ensureMsgf(false, TEXT("IA_Move is disabled"));
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



void ABasePlayerController::OnZoomIn(const FInputActionValue& InputActionValue)
{
	UCameraComponent* CameraComponent = GetPawn()->GetComponentByClass<UCameraComponent>();

	// Pressing 활성화시 해당 부분 주석을 풀어주세요
	//SpringArm->SetDesiredZoom(160.f);
	//CameraComponent->AddRelativeLocation(FVector(0, 100, 0));
	//IsZoom = true;

	//Changed Pressed
	if (!IsZoom)
	{
		//Zoom 상태 돌입
		SpringArm->SetDesiredZoom(160.f);

		CameraComponent->AddRelativeLocation(FVector(0, 100, 0));
		IsZoom = true;
	}
	else if (IsZoom)
	{
		SpringArm->SetDesiredZoom(400.f);
		CameraComponent->AddRelativeLocation(FVector(0, -100, 0));
		IsZoom = false;
	}
}

// Pressing 활성화시 해당 부분 주석을 풀어주세요
//void ABasePlayerController::OnZoomOut(const FInputActionValue& InputActionValue)
//{
//	//Camera Setting 2 Can Change 
//	SpringArm->SetDesiredZoom(400.f);
//	UCameraComponent* CameraComponent = GetPawn()->GetComponentByClass<UCameraComponent>();
//	if (IsZoom)
//	{
//		CameraComponent->AddRelativeLocation(FVector(0, -100, 0));
//		IsZoom = false;
//	}
//}

void ABasePlayerController::OnATK(const FInputActionValue& InputActionValue)
{

}
