// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	void SetOwningPawn(APawn* NewPawn) { OwningPawn = NewPawn; }
	APawn* GetOwningPawn() const { return OwningPawn; }
protected:
	UPROPERTY()
	APawn* OwningPawn = nullptr;

};
