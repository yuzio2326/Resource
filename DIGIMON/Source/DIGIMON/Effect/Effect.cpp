// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/Effect.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ActorPoolSubsystem.h"


// Sets default values
AEffect::AEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(DefaultSceneRoot);
	ParticleSystemComponent->bAutoActivate = false;
	RootComponent = DefaultSceneRoot;
}

void AEffect::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{

}

void AEffect::Play()
{
}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEffect::PlaySound()
{
}

void AEffect::PlayParticle()
{
}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FEffectTableRow::FEffectTableRow()
	: EffectClass(AEffect::StaticClass())
{
}
