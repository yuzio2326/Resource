// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseUsableItem.h"
#include "Character/BasePlayer.h"

// Sets default values
ABaseUsableItem::ABaseUsableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseUsableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseUsableItem::SetData()
{

}

void ABaseUsableItem::UseItem()
{
	

}

// Called every frame
void ABaseUsableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//BasePlayer의 status 나 가지고있는 디지몬에게 사용 가능하도록 할 예정


}

FUsableItem::FUsableItem()
{
	// 0 weapon 1 usable 2 digimon 3 Other(기타템)
	//itemtype = 1;
}
