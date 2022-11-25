// Copyright 2023 mozahzah. All Rights Reserved.

using UnrealBuildTool;

public class ProjectAlpha : ModuleRules
{
	public ProjectAlpha(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
	}
}