#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

#include "GlobalVariables.h"
#include "InGameFunctions.h"

//variables
int hotkeyToggleForceHeat, hotkeyForceHeatLevel, hotkeyToggleCops, hotkeyToggleCopLights, hotkeyToggleHeadlights, hotkeyFreezeCamera, hotkeyUnlockAllThings, hotkeyAutoDrive, CareerSingleRace, CareerBattle, CareerChallenge, TrafficLow, TrafficMed, TrafficHigh, ForceCarLOD, ForceTireLOD, StartingCash, ProducerDemoStartingCash;
bool EnableSaveLoadHotPos, ShowLanguageSelectScreen, ExOptsTeamTakeOver, EnableDebugWorldCamera, UnlockAllThings, ForceCollectorsEdition, EnableHeatLevelOverride, SkipMovies, SkipNISs, EnableSound, EnableMusic, ShowMessage, SkipCareerIntro, ProducerDemo, SkipPSA, DisableBootupOnlineLogin, DisableDoubleTapBrakeToReverse, PursuitActionMode, ForceStraightPursuit, ShowPursuitCops, ShowNonPursuitCops, UncensoredBustedScreen, NoRevLimiter;
char const* PlayerName;
float GameSpeed, MinHeatLevel, MaxHeatLevel, CarSelectTireSteerAngle, RadarRange, SpeedingLimit, ExcessiveSpeedingLimit, RecklessDrivingLimit;

#include "EAMemcard.h"
#include "FESplashScreen.h"
#include "Game.h"

#include "CodeCaves.h"
#include "Helpers.h"
#include "HotkeyStuff.h"

void Init()
{
	// Read INI file
	CIniReader iniReader("NFSUCExtraOptionsSettings.ini");
	// Hotkeys
	hotkeyToggleForceHeat = iniReader.ReadInteger("Hotkeys", "HeatLevelHack", 118); // F7
	hotkeyForceHeatLevel = iniReader.ReadInteger("Hotkeys", "ChangeHeatLevel", 33); // PageUp
	hotkeyToggleCops = iniReader.ReadInteger("Hotkeys", "ToggleCops", 145); // Scroll Lock
	hotkeyToggleCopLights = iniReader.ReadInteger("Hotkeys", "CopLights", 79); // O
	hotkeyToggleHeadlights = iniReader.ReadInteger("Hotkeys", "Headlights", 72); // H
	hotkeyFreezeCamera = iniReader.ReadInteger("Hotkeys", "FreezeCamera", 19); // Pause/Break
	hotkeyUnlockAllThings = iniReader.ReadInteger("Hotkeys", "UnlockAllThings", 116); //F5
	hotkeyAutoDrive = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); //F6
	EnableSaveLoadHotPos = iniReader.ReadInteger("Hotkeys", "EnableSaveLoadHotPos", 0) != 0;

	// OpponentControllers
	CareerSingleRace = iniReader.ReadInteger("OpponentControllers", "CareerSingleRace", 7);
	CareerBattle = iniReader.ReadInteger("OpponentControllers", "CareerBattle", 1);
	CareerChallenge = iniReader.ReadInteger("OpponentControllers", "CareerChallenge", 0);

	// TrafficControllers
	TrafficLow = iniReader.ReadInteger("TrafficControllers", "Low", 10);
	TrafficMed = iniReader.ReadInteger("TrafficControllers", "Medium", 20);
	TrafficHigh = iniReader.ReadInteger("TrafficControllers", "High", 40);

	// Menu
	ShowLanguageSelectScreen = iniReader.ReadInteger("Menu", "ShowLanguageSelectScreen", 0) != 0;
	CarSelectTireSteerAngle = iniReader.ReadFloat("Menu", "CarSelectTireSteerAngle", 13.0f);
	ExOptsTeamTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableDebugWorldCamera = iniReader.ReadInteger("Gameplay", "EnableDebugCamera", 0) != 0;
	GameSpeed = iniReader.ReadFloat("Gameplay", "GameSpeed", 1.0f);
	static auto _PlayerName = iniReader.ReadString("Gameplay", "PlayerName", "0");
	PlayerName = _PlayerName.c_str();
	UnlockAllThings = iniReader.ReadInteger("Gameplay", "UnlockAllThings", 0) != 0;
	StartingCash = iniReader.ReadInteger("Gameplay", "StartingCash", 0);
	ProducerDemoStartingCash = iniReader.ReadInteger("Gameplay", "ProducerDemoStartingCash", 10000000);
	ForceCollectorsEdition = iniReader.ReadInteger("Gameplay", "ForceCollectorsEdition", 1) != 0;
	NoRevLimiter = iniReader.ReadInteger("Gameplay", "NoRevLimiter", 0) != 0;
	DisableDoubleTapBrakeToReverse = iniReader.ReadInteger("Gameplay", "DisableDoubleTapBrakeToReverse", 1) != 0;

	// Pursuit
	EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 0) != 0;
	MinHeatLevel = iniReader.ReadFloat("Pursuit", "MinimumHeatLevel", 1.00f);
	MaxHeatLevel = iniReader.ReadFloat("Pursuit", "MaximumHeatLevel", 5.00f);
	PursuitActionMode = iniReader.ReadInteger("Pursuit", "PursuitActionMode", 0) != 0;
	ForceStraightPursuit = iniReader.ReadInteger("Pursuit", "ForceStraightPursuit", 0) != 0;
	ShowPursuitCops = iniReader.ReadInteger("Pursuit", "ShowPursuitCops", 1) != 0;
	ShowNonPursuitCops = iniReader.ReadInteger("Pursuit", "ShowNonPursuitCops", 1) != 0;
	RadarRange = iniReader.ReadFloat("Pursuit", "RadarRange", 300.0f);
	UncensoredBustedScreen = iniReader.ReadInteger("Pursuit", "UncensoredBustedScreen", 0) != 0;
	SpeedingLimit = iniReader.ReadFloat("Pursuit", "SpeedingLimit", 44.704f);
	ExcessiveSpeedingLimit = iniReader.ReadFloat("Pursuit", "ExcessiveSpeedingLimit", 67.056f);
	RecklessDrivingLimit = iniReader.ReadFloat("Pursuit", "RecklessDrivingLimit", 89.408f);

	// Misc
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) != 0;
	SkipNISs = iniReader.ReadInteger("Misc", "SkipNISs", 0) != 0;
	SkipPSA = iniReader.ReadInteger("Misc", "SkipPSA", 0) != 0;
	DisableBootupOnlineLogin = iniReader.ReadInteger("Misc", "DisableBootupOnlineLogin", 0) != 0;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) != 0;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) != 0;
	ShowMessage = iniReader.ReadInteger("Misc", "ShowMessage", 1) != 0;
	SkipCareerIntro = iniReader.ReadInteger("Misc", "SkipCareerIntro", 0) != 0;
	ProducerDemo = iniReader.ReadInteger("Misc", "ProducerDemo", 0) != 0;
	ForceCarLOD = iniReader.ReadInteger("Misc", "ForceCarLOD", -1);
	ForceTireLOD = iniReader.ReadInteger("Misc", "ForceTireLOD", -1);

	// Restrictions (wrap values around)
	CareerSingleRace %= 8;
	CareerBattle %= 8;
	CareerChallenge %= 8;

	TrafficLow %= 101;
	TrafficMed %= 101;
	TrafficHigh %= 101;

	// Opponent Controllers
	injector::WriteMemory<int>(0x642FA7, CareerSingleRace, true);
	injector::WriteMemory<int>(0x642F9E, CareerBattle, true);
	injector::WriteMemory<int>(0x642F95, CareerChallenge, true);

	// Traffic Density Controllers (0-100)
	injector::WriteMemory<int>(0xBFC25C, TrafficLow, true); // Low
	injector::WriteMemory<int>(0xBFC260, TrafficMed, true); // Medium
	injector::WriteMemory<int>(0xBFC264, TrafficHigh, true); // High

	// todo: add stuff

	// Force disable Online Login from BootFlow (can also be disabled in online options per save file)
	if (DisableBootupOnlineLogin)
		injector::MakeJMP(0x005E7BDB, 0x5E7C1B, true);

	// PSAScreen disable - reroute it to the MovieScreen, because if we actually disable it, game doesn't finish loading everything
	if (SkipPSA)
		injector::WriteMemory<BYTE>(0x005E774B, 0x3A, true);

	// Language Select Screen
	if (ShowLanguageSelectScreen)
	{
		// FEBootFlowStateManager::InitStateList
		injector::WriteMemory<BYTE>(0x5E76CE, 0xB8, true); // mov eax,1
		injector::WriteMemory<DWORD>(0x5E76CF, 1, true);

		// Show all languages
		injector::WriteMemory<BYTE>(0x69DB16, 0xEB, true); // sub_69DB10
		injector::WriteMemory<BYTE>(0x5E80A9, 13, true); // FEBootFlowStateManager::BuildLanguageList
	}

	// Race Speed Multiplier
	injector::WriteMemory<float>(_Tweak_GameSpeed, GameSpeed, true);

	// Player Name stuff
	// QuickGame::CreatePlayers
	injector::MakeRangedNOP(0x7BB3FF, 0x7BB409, true); // Get player name with stringhash
	injector::MakeRangedNOP(0x7BB40F, 0x7BB412, true); // add esp,4
	injector::MakeCALL(0x7BB3FF, EA_Memcard_IMemcardFile_GetFilename, true);

	// Starting Cash
	injector::MakeJMP(0x647E17, StartingCashCodeCave, true); // GMW2Game::StartNewCareer
	injector::WriteMemory<int>(0x5E77E3, ProducerDemoStartingCash, true); // FEBootFlowStateManager::InitStateList

	// Force Collectors Edition
	if (ForceCollectorsEdition)
	{
		injector::MakeRangedNOP(0x52555E, 0x525561, true); // DALCareer::SetInt
		injector::WriteMemory<WORD>(0x0052555E, 0x01B2, true); // mov dl,1
		injector::WriteMemory<BYTE>(_IsCollectorsEdition, 1, true);
	}

	// Hook splash screen
	if (ExOptsTeamTakeOver)
	{
		injector::WriteMemory(0xBEC0E0, &FE_FESplashScreen_InitializeScreenAptFuncs, true);
	}

	// No rev limiter
	if (NoRevLimiter)
	{
		injector::WriteMemory(0xC1C688, &Return0Hook, true); // Engine::`vftable'{for `Sim::IServiceable'}, Engine::UseRevLimiter(void)
		injector::WriteMemory(0xC1C8A0, &Return0Hook, true); // EngineRacer::`vftable'{for `Sim::IServiceable'}, Engine::UseRevLimiter(void)
		injector::WriteMemory(0xC1CAC8, &Return0Hook, true); // EngineSpline::`vftable'{for `Sim::IServiceable'}, Engine::UseRevLimiter(void)
		injector::WriteMemory(0xC1CCE0, &Return0Hook, true); // EngineTraffic::`vftable'{for `Sim::IServiceable'}, Engine::UseRevLimiter(void)
	}

	// Disable Double-Tap Brake to shift to Reverse
	if (DisableDoubleTapBrakeToReverse)
	{
		injector::WriteMemory<float*>(0x428DC7, &ZeroFloat, true); // disable double tap to reverse
	}

	// Unlock All Things
	injector::WriteMemory<BYTE>(_UnlockAllThings, UnlockAllThings, true);

	// Heat Level Override
	ToggleHeatLevelOverride(EnableHeatLevelOverride);
	injector::MakeJMP(0x432E07, ForceMaxHeatCodeCave_AIVehiclePerp_SetHeat, true); // AIVehiclePerp::SetHeat, Code cave to overide attributes.bin > heat > general_max_heat_level
	injector::MakeJMP(0x4440FA, ForceMaxHeatCodeCave_AIVehicleHuman_dt, true); // AIVehicleHuman::~AIVehicleHuman
	injector::MakeJMP(0x69758A, ForceMaxHeatCodeCave_EBountyPointsGained_dt, true); // EBountyPointsGained::~EBountyPointsGained, also has OOB fix
	injector::MakeJMP(0x41A8D4, FixArrayOOBCodeCave_AIVehicleCopCar_CheckForPursuitForHeat, true); // AIVehicleCopCar::CheckForPursuitForHeat
	injector::MakeJMP(0x41AA54, FixArrayOOBCodeCave_AIVehicleCopCar_CheckForPursuitForSpeed, true); // AIVehicleCopCar::CheckForPursuitForSpeed
	injector::MakeJMP(0x41ABCE, FixArrayOOBCodeCave_AIVehicleCopCar_CheckForPursuitFor911Call, true); // AIVehicleCopCar::CheckForPursuitFor911Call
	injector::MakeJMP(0x438142, FixArrayOOBCodeCave_AICopManager_SpawnPatrolCar, true); // AICopManager::CheckForPursuitForHeat

	// Pursuit Action Game Mode - Harder Pursuits in Quick Races
	if (PursuitActionMode)
	{
		// Replace Race Table (0x2283ECAF) with Threat Table (0xCA489018)
		injector::WriteMemory<DWORD>(0x417F47, 0xCA489018, true); // AIPursuit::RefreshEscalationTables

		// Replace Race Support (0xE5332008) with Threat Support (0xF3918F68)
		injector::WriteMemory<DWORD>(0x417FB2, 0xF3918F68, true); // AIPursuit::RefreshEscalationTables

		// Can Spawn Roadblocks in Quick Race
		//injector::MakeNOP(0x409E60, 6, true); // AIPursuit::RequestRoadBlock

		// Cops Can Call Support in Quick Race
		//injector::MakeNOP(0x418877, 2, true); // AIPursuit::RequestGroundSupport

		// Helicopter
		//injector::MakeNOP(0x41854B, 2, true); // AIPursuit::CopRequest

	}

	// Force Straight Pursuit (No support units or roadblocks)
	if (ForceStraightPursuit) injector::WriteMemory<int>(_Tweak_ForceStraightPursuit, ForceStraightPursuit, true);

	// Show Pursuit Cops
	injector::WriteMemory<BYTE>(_MinimapShowPursuitCops, ShowPursuitCops, true);

	// Show Non-Pursuit Cops
	injector::WriteMemory<BYTE>(_MinimapShowNonPursuitCops, ShowNonPursuitCops, true);

	// Radar Range
	injector::WriteMemory<float>(_Tweak_RadarRange, RadarRange, true);

	// Uncensored Busted Screen
	if (UncensoredBustedScreen)
	{
		injector::WriteMemory<BYTE>(0x457D15, 0x00, true); // sub_457830, FacePixelation::mPixelationOn = 0
		injector::WriteMemory<BYTE>(0x45A944, 0x00, true); // sub_45A7C0
	}

	// Infractions
	injector::WriteMemory<float>(_Tweak_SpeedingLimit, SpeedingLimit, true);
	injector::WriteMemory<float>(_Tweak_RacingLimit, ExcessiveSpeedingLimit, true);
	injector::WriteMemory<float>(_Tweak_RecklessDrivingLimit, RecklessDrivingLimit, true);

	// Handle Misc Options
	if (SkipMovies) injector::WriteMemory<BYTE>(_SkipMovies, SkipMovies, true);
	//if (SkipNISs) injector::WriteMemory<BYTE>(_SkipNISs, SkipNISs, true);
	if (EnableSound) injector::WriteMemory<BYTE>(_IsSoundEnabled, EnableSound, true);
	if (EnableMusic) injector::WriteMemory<BYTE>(_IsAudioStreamingEnabled, EnableMusic, true);
	if (SkipCareerIntro) injector::WriteMemory<BYTE>(_SkipCareerIntro, SkipCareerIntro, true);
	if (ProducerDemo) injector::WriteMemory<BYTE>(_ProducerDemo, ProducerDemo, true);

	// Force Car and Tire LOD
	injector::WriteMemory<int>(_ForceCarLOD, ForceCarLOD, true);
	injector::WriteMemory<int>(_ForceTireLOD, ForceTireLOD, true);
	
	// Menu Front Tire Angle
	injector::WriteMemory<float>(_CarSelectTireSteerAngle, CarSelectTireSteerAngle, true);

	// Hook the hotkey detection to the renderer
	injector::MakeCALL(0x7B44EE, Thing, true); //eDisplayFrame
}