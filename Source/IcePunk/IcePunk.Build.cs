// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IcePunk : ModuleRules
{
	public IcePunk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",  "GameplayTasks","AnimGraphRuntime", "AnimationCore", "UnrealEd", "EditorScriptingUtilities","EnhancedInput","UMG","NavigationSystem","AIModule" });
	}
}
