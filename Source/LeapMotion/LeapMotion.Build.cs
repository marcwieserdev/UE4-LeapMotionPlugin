// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class LeapMotion : ModuleRules
	{
		public LeapMotion(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					"LeapMotion/Public",
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"LeapMotion/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Engine",
					"Core",
                    "CoreUObject",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
            PublicAdditionalLibraries.Add("Leap.lib");
		}
	}
}