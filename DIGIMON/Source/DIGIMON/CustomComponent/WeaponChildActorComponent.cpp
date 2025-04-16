// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/BaseWeapon.h"
#include "CustomComponent/WeaponChildActorComponent.h"

UWeaponChildActorComponent::UWeaponChildActorComponent()
{
	SetChildActorClass(ABaseWeapon::StaticClass());
}

void UWeaponChildActorComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	if (InDataTableRowHandle.IsNull()) { return; }
	FWeaponTableRow* Data = InDataTableRowHandle.GetRow<FWeaponTableRow>(TEXT("Weapon"));
	if (!Data) { ensure(false); return; }

	if (GetChildActorClass() != Data->WeaponClass)
	{
		SetChildActorClass(Data->WeaponClass);
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);
	ABaseWeapon* Weapon = Cast<ABaseWeapon>(GetChildActor());
	check(Weapon);
	if (Weapon == nullptr) { return; }

	Weapon->SetOwner(OwnerPawn);
	Weapon->SetInstigator(OwnerPawn);
}
