// Copyright Fabian Fröding 2024. All Right Reserved.

using UnrealBuildTool;

public class Nara : ModuleRules
{
	public Nara(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks" 
		});

        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem", "Niagara" });
    }
}
