// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
//using System; //언제 생겼지?

public class DIGIMONServerTarget : TargetRules
{
	public DIGIMONServerTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Server; ;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("DIGIMON");

        ExtraModuleNames.Remove("Graphics");

    }
}
