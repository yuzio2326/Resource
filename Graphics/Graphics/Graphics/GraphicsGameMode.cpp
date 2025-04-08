// Fill out your copyright notice in the Description page of Project Settings.


#include "Graphics/GraphicsGameMode.h"

void AGraphicsGameMode::BeginPlay()
{
	Super::BeginPlay();


    // ViewExtension 생성 및 설정
    MyViewExtension = FSceneViewExtensions::NewExtension<FMyViewExtension>();

    // 원하는 StaticMesh 및 색상 설정
    UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh)
    {
        MyViewExtension->SetStaticMesh(CubeMesh);
        MyViewExtension->SetColor(FLinearColor::Red);
    }

}