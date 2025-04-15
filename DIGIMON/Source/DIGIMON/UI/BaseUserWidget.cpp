// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseUserWidget.h"

void UBaseUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBaseUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ensure(OwningPawn);
}
