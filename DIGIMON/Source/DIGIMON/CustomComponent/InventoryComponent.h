// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Item/BaseItem.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenInventory, bool, IsOpenInventory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGIMON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetData(FDataTableRowHandle InDataTableRowHandle);

	//Player 는 아이템을 사용하도록 합니다, 보유한 아이템은 모두 아이템Id 갯수를 저장을 해놓고 불러올때 id를 찾아서 맞는 아이템 불러오고
	//해당하는 갯수 만큼 가지고 오도록 한다 
	//UseItem을 할때는 해당하는 아이템의 type을 가지고 와서 알맞은 형태로 사용 / equip 류는 자기한테 맞는 equip창의 아이템과 교환
	//usable은 해당하는 창을 불러와서 사용 대상 눌러서 사용 UI 의 Temp_UseItemTarget을 참고하도록 
	// 기능 추가중이라 하직 안됌
	//void UseItem(FItemTableRow* InItemTableRow);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 인벤 열리고 닫히는거 아이템 사용, 이동(드래그 드롭)
	UFUNCTION(BlueprintCallable)
	void OpenInventory(bool OpeningInventory);

public:
	//UI 쪽에서 button action으로 해당 값을 바꾸도록 하고 해당 값에 따라서 visable을 바꾸도록 한다.
	UPROPERTY(EditAnywhere)
	bool IsOpenInventory = false;

	UPROPERTY(BlueprintAssignable)
	FOpenInventory	OnInventory;

	//가지고 오가는 아이템들
	UPROPERTY(BlueprintAssignable)
	FItemTableRow ItemTableRow;
};
