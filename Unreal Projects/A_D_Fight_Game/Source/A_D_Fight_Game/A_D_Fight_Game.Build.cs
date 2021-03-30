// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class A_D_Fight_Game : ModuleRules
{
	public A_D_Fight_Game(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
