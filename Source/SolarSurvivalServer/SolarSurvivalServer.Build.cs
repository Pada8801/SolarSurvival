// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class SolarSurvivalServer : ModuleRules
{
    public SolarSurvivalServer(TargetInfo Target)
    {
        PrivateIncludePaths.Add("../../SolarSurvival/Source/SolarSurvivalServer");
        PrivateIncludePaths.Add("../../SolarSurvival/Source/SolarSurvivalServer/ServerGameMode");
        PrivateIncludePaths.Add("../../SolarSurvival/Source/SolarSurvivalServer/ServerGameSession");
        PrivateIncludePaths.Add("../../SolarSurvival/Source/SolarSurvivalServer/ServerOnlineGameSettingsBase");
        PrivateIncludePaths.Add("../../SolarSurvival/Source/SolarSurvival");

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "OnlineSubsystem", "OnlineSubsystemUtils"
        ,"Steamworks", "Sockets", "Networking", "SQLiteSupport"});

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

        PublicDependencyModuleNames.Add("SolarSurvival");
        CircularlyReferencedDependentModules.Add("SolarSurvival");
    }
}
