// Copyright Epic Games, Inc. All Rights Reserved.

#include "Graphics.h"
#include "Modules/ModuleManager.h"


void FGraphicsModule::StartupModule()
{
	IModuleInterface::StartupModule();

	FString ShaderDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/KDT3D"), ShaderDir);
}

IMPLEMENT_MODULE(FGraphicsModule, GraphicsModule);
