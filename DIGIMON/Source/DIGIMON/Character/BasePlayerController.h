// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"
#include "Engine/DataAsset.h"
#include "Character/BasePlayer.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn);


protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);

	void OpenInventory(const FInputActionValue& InputActionValue);
	void ShowCursor();

	void OnZoomIn(const FInputActionValue& InputActionValue);
	// Pressing 활성화시 해당 부분 주석을 풀어주세요
	//void OnZoomOut(const FInputActionValue& InputActionValue);
	void OnATK(const FInputActionValue& InputActionValue);
	void OffATK(const FInputActionValue& InputActionValue);


protected:
	UInputMappingContext* IMC_BasePlayer = nullptr;
	class USoftWheelSpringArmComponent* SpringArm = nullptr;

	UPROPERTY()
	class UStatusComponent* StatusComponent;
	UPROPERTY()
	class USkillComponent* SkillComponent;
	UPROPERTY()
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsAttack = false;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsOpenInventory = false;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsZoom = false;

};
