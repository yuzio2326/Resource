// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseOwnDigimon.h"

// Sets default values
ABaseOwnDigimon::ABaseOwnDigimon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseOwnDigimon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{

}

// Called when the game starts or when spawned
void ABaseOwnDigimon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseOwnDigimon::SpawnOwnMonster()
{

}

// Called every frame
void ABaseOwnDigimon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

