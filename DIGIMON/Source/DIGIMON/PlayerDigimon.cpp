// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDigimon.h"

// Sets default values
APlayerDigimon::APlayerDigimon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerDigimon::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerDigimon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void APlayerDigimon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{

}

// Called every frame
void APlayerDigimon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerDigimon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

