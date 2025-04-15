// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HPBarWidget.h"
#include "CustomComponent/StatusComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UHPBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHPBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* Pawn = GetOwningPawn();
	UStatusComponent* StatusComponent = Pawn->GetComponentByClass<UStatusComponent>();
	check(StatusComponent);

	if (StatusComponent != nullptr)
	{
		StatusComponent->OnHPChanged.AddDynamic(this, &ThisClass::OnHPChanged);
		StatusComponent->OnDie.AddDynamic(this, &ThisClass::OnDie);
	}
	else
		return;
	SetVisibility(ESlateVisibility::Visible);	//check 이후 Hidden으로 바꾸기
}

void UHPBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UHPBarWidget::OnHiddenUI()
{
	SetVisibility(ESlateVisibility::Hidden); //check 이후 Hidden으로 바꾸기
}

void UHPBarWidget::OnHPChanged(float CurrentHP, float MaxHP)
{
	if (FMath::IsNearlyZero(MaxHP))
	{
		ensureMsgf(false, TEXT("MaxHP is nearly zero"));
		return;
	}
	SetVisibility(ESlateVisibility::Visible);
	const float Percent = CurrentHP / MaxHP;
	HPBar->SetPercent(Percent);

	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), 3.f, false);
}

void UHPBarWidget::OnDie()
{
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), 2.f, false);
}

void UHPBarWidget::OnDeath(bool IsDead)
{
	if (IsDead)
	{
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnHiddenUI"), 2.f, false);
	}
}
