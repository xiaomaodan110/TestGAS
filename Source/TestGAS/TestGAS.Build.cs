// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestGAS : ModuleRules
{
	public TestGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// close optimize.
		OptimizeCode = CodeOptimization.Never;

		PublicIncludePaths.AddRange(new string[] {
			"TestGAS",
			"TestGAS/AbilitySystem",
            "TestGAS/AbilitySystem/Abilities",
            "TestGAS/AbilitySystem/Attributes",
            "TestGAS/AbilitySystem/Excutions",
            "TestGAS/Character",
            "TestGAS/Component",
            "TestGAS/DamagedActor",
            "TestGAS/FeedBack",
            "TestGAS/FeedBack/NumberPopComponent",
            "TestGAS/GameMode",
            "TestGAS/Item",
            "TestGAS/Notify",
            "TestGAS/NotifyState",
            "TestGAS/Player",
            "TestGAS/System",
            "TestGAS/UI",
            "TestGAS/UI/CharacterInfo",
            "TestGAS/UI/Common",
            "TestGAS/UI/Core",
            "TestGAS/UI/Damage",
            "TestGAS/UI/Equipment",
            "TestGAS/UI/Inventory",
        });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
			"GameplayAbilities", 
			"GameplayTasks", 
			"GameplayTags",
			"Slate",
			"SlateCore",
			"HTTP",
			"JsonUtilities",
			"Json",
			"ModularGameplay",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
