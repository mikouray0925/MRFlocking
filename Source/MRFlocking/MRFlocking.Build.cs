// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MRFlocking : ModuleRules
{
	public MRFlocking(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
