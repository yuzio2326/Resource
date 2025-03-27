// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnData.h"

// Sets default values
APawnData::APawnData()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APawnData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnData::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

