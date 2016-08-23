// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SolarSurvival : ModuleRules
{
	public SolarSurvival(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem", "OnlineSubsystemUtils", "AIModule"
            ,"UMG", "Slate", "SlateCore" , "Steamworks", "GameplayAbilities", "GameplayTags","GameplayTasks"});  //GameplayAbilities
        bFasterWithoutUnity = true;

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		//where we will include our Server side only module for Dedicated servers
		if (UEBuildConfiguration.bWithServerCode == true)
		{
			PublicDependencyModuleNames.Add("SolarSurvivalServer");
			CircularlyReferencedDependentModules.Add("SolarSurvivalServer");
			
		}
	}
}
