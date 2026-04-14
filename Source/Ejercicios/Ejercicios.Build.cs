// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ejercicios : ModuleRules
{
	public Ejercicios(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Ejercicios",
			"Ejercicios/Variant_Platforming",
			"Ejercicios/Variant_Platforming/Animation",
			"Ejercicios/Variant_Combat",
			"Ejercicios/Variant_Combat/AI",
			"Ejercicios/Variant_Combat/Animation",
			"Ejercicios/Variant_Combat/Gameplay",
			"Ejercicios/Variant_Combat/Interfaces",
			"Ejercicios/Variant_Combat/UI",
			"Ejercicios/Variant_SideScrolling",
			"Ejercicios/Variant_SideScrolling/AI",
			"Ejercicios/Variant_SideScrolling/Gameplay",
			"Ejercicios/Variant_SideScrolling/Interfaces",
			"Ejercicios/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
