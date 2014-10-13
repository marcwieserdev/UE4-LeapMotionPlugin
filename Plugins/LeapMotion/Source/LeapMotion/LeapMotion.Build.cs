// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class LeapMotion : ModuleRules
	{
        private string ModulePath
        {
            get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
        }

        private string LibraryPath
        {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "Private/libs")); }
        }

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
                    "LeapMotion/Private/Interface"
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Engine",
					"Core",
                    "CoreUObject",
                    "Slate",
                    "HeadMountedDisplay"
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

            LoadLeapLib(Target);
		}

        public bool LoadLeapLib(TargetInfo Target)
        {
            bool isLibrarySupported = false;

            if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
            {
                isLibrarySupported = true;
                
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "Leap.lib"));
            }

            return isLibrarySupported;
        }
	}
}