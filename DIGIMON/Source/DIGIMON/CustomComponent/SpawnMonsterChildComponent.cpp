// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/PartyMonster.h"
#include "CustomComponent/SpawnMonsterChildComponent.h"

USpawnMonsterChildComponent::USpawnMonsterChildComponent()
{
	SetChildActorClass(APartyMonster::StaticClass());
}

void USpawnMonsterChildComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	if (InDataTableRowHandle.IsNull()) { return; }
	FPartyMonsterTableRow* Data = InDataTableRowHandle.GetRow<FPartyMonsterTableRow>(TEXT("PartyMonster"));
	if (!Data) { ensure(false); return; }

	if (GetChildActorClass() != Data->PartyMonsterClass)
	{
		SetChildActorClass(Data->PartyMonsterClass);
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn);
	ABasePlayer* OwnerPlayer = Cast<ABasePlayer>(GetOwner());
	check(OwnerPlayer);
	APartyMonster* PartyMonster = Cast<APartyMonster>(GetChildActor());
	check(PartyMonster);
	if (PartyMonster == nullptr) { return; }

	PartyMonster->SetOwnerPlayer(OwnerPlayer);
	

}
