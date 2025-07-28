// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Item/BaseItem.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


USTRUCT()	//Item관리용
struct DIGIMON_API FDropTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (RowType = "/Script/DIGIMON.ItemTableRow"))
	TArray<FDataTableRowHandle> ItemDataArray;

};


// 안써도될지도?
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenInventory, bool, IsOpenInventory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGIMON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	struct PlayerInventoryItem
	{
		//item id
		uint8 OwnedItemID;

		//Owned item stack
		uint8 OwnedItemStack;


	};

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetData(FDataTableRowHandle InDataTableRowHandle);

	//Player는 아이템을 사용하도록 합니다, 보유한 아이템은 모두 아이템Id 갯수를 저장을 해놓고 불러올때 id를 찾아서 맞는 아이템 불러오고
	//해당하는 갯수 만큼 가지고 오도록 한다 
	//UseItem을 할때는 해당하는 아이템의 type을 가지고 와서 알맞은 형태로 사용 / equip 류는 자기한테 맞는 equip창의 아이템과 교환
	//usable은 해당하는 창을 불러와서 사용 대상 눌러서 사용 UI 의 Temp_UseItemTarget을 참고하도록 
	// 기능 추가중이라 하직 안됌
	//void UseItem(FItemTableRow* InItemTableRow);
	// 
	// 상점이나 상자를 이용할때는 서로의 inventory 창만 띄우고 status나 다른것들은 안띄우도록 하기(Wd_Maininventory 말고 Wd_inventory만)

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Usable item Party 등 분류 전에 사용
	UFUNCTION(BlueprintCallable)
	void UseItem();
	//Partner와 장비는 해당 기능을 사용할 예정
	//void UseItemEquip();
	// 소모품 아이템은 해당 기능 사용 예정
	//void UseItemUsable();

public:
	// 인벤 열리고 닫히는거 아이템 사용, 이동(드래그 드롭)
	UFUNCTION(BlueprintCallable)
	void OpenInventory(bool OpeningInventory);

public:
	//UI 쪽에서 button action으로 해당 값을 바꾸도록 하고 해당 값에 따라서 visable을 바꾸도록 한다.
	UPROPERTY(EditAnywhere)
	bool IsOpenInventory = false;

	//UPROPERTY(BlueprintAssignable)
	//FOpenInventory	OnInventory;

public:
	//가지고 오가는 아이템들
	
	//player가 가지고 있는 아이템
	//UPROPERTY()
	//TArray<PlayerInventoryItem> PlayerOwnedItems;

	// 아이템 정보는 여기// 이후 아이템은 struct로 저장하는게 좋음 
	UPROPERTY()
	FItemTableRow ItemTable;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.ItemTableRow"))
	FDataTableRowHandle DataTableRowHandle;
	

};
