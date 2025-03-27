// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/MeleeATK.h"

// Sets default values
AMeleeATK::AMeleeATK()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMeleeATK::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{

}

// Called when the game starts or when spawned
void AMeleeATK::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeATK::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FMeleeATKTableRow::FMeleeATKTableRow()
	: MeleeATKClass(AMeleeATK::StaticClass())
{
	//Check to Create StaticClass
	int a = 0;
}
