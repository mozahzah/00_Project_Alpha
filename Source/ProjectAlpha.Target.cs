// Copyright 2023 mozahzah. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectAlphaTarget : TargetRules
{
	public ProjectAlphaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ProjectAlpha");
		WindowsPlatform.PCHMemoryAllocationFactor = 2000;
	}
}
