// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DIGIMON : ModuleRules
{
	public DIGIMON(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
