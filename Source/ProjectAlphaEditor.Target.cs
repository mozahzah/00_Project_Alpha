// Copyright 2023 mozahzah. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectAlphaEditorTarget : TargetRules
{
	public ProjectAlphaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ProjectAlpha");
		WindowsPlatform.PCHMemoryAllocationFactor = 2000;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
	}
}
