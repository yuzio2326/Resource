// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemAction.h"
#include "SubSystem/ItemSubsystem.h"
#include "CustomComponent/WeaponChildActorComponent.h"

void UItemAction_Weapon::Use()
{
	if (UWorld* World = Context->User->GetWorld())
	{
		UItemSubsystem* Subsystem = World->GetGameInstance()->GetSubsystem<UItemSubsystem>();
		FDataTableRowHandle Handle = Subsystem->FindItem(Context->ItemName);
		if (Handle.IsNull())
		{
			ensureMsgf(false, TEXT("Handle is not valid"));
			return;
		}

		APawn* Pawn = Context->User->GetPawn();

		UWeaponChildActorComponent* Weapon = Pawn->GetComponentByClass<UWeaponChildActorComponent>();
		check(Weapon);
		Weapon->SetData(Handle);

	}

	Super::Use();
}
