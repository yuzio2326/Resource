// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/ItemSubsystem.h"

UItemSubsystem::UItemSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Digimon/Data/Item/DT_Weapon.DT_Weapon'"));
		check(Asset.Object);
		WeaponDataTable = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Digimon/Data/Item/DT_Usable.DT_Usable'"));
		check(Asset.Object);
		UsableDataTable = Asset.Object;
	}
	// 나중에 디지몬 만들고 여기에 추가하기 reference 바꾸기 ㄱㄱ ... 아니다
	//{
	//	static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Digimon/Data/Item/DT_Usable.DT_Usable'"));
	//	check(Asset.Object);
	//	UsableDataTable = Asset.Object;
	//}

}

FDataTableRowHandle UItemSubsystem::FindItem(const FName& InKey)
{
	FDataTableRowHandle DataTableRowHandle;

#if WITH_EDITOR
	bool bFind = false;
	if (WeaponDataTable->GetRowMap().Find(InKey))
	{
		check(!bFind);
		bFind = true;
		DataTableRowHandle.DataTable = WeaponDataTable;
		DataTableRowHandle.RowName = InKey;
	}
	if (UsableDataTable->GetRowMap().Find(InKey))
	{
		check(!bFind);
		bFind = true;
		DataTableRowHandle.DataTable = UsableDataTable;
		DataTableRowHandle.RowName = InKey;
	}
	//if (ItemPackDataTable->GetRowMap().Find(InKey))
	//{
	//	check(!bFind);
	//	bFind = true;
	//	DataTableRowHandle.DataTable = ItemPackDataTable;
	//	DataTableRowHandle.RowName = InKey;
	//}
#else
	if (WeaponDataTable->GetRowMap().Find(InKey))
	{
		DataTableRowHandle.DataTable = WeaponDataTable;
		DataTableRowHandle.RowName = InKey;
	}
	else if (GunDataTable->GetRowMap().Find(InKey))
	{
		DataTableRowHandle.DataTable = GunDataTable;
		DataTableRowHandle.RowName = InKey;
	}
	//else if (ItemPackDataTable->GetRowMap().Find(InKey))
	//{
	//	DataTableRowHandle.DataTable = ItemPackDataTable;
	//	DataTableRowHandle.RowName = InKey;
	//}
#endif

	return DataTableRowHandle;
}
