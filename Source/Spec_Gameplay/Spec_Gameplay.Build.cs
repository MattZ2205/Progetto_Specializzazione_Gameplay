// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Spec_Gameplay : ModuleRules
{
	public Spec_Gameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
