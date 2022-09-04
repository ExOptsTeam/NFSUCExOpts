#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

DWORD TheGameFlowManager;
bool IsOnFocus, IsNotPaused, AutoDrive, DebugCamStatus, DebugWatchCarCamera, copLightsEnabled, forceHeatLevel, ToggleCops = 1;
float heatLevel;

void Thing()
{
	_asm pushad;

	TheGameFlowManager = *(DWORD*)_TheGameFlowManager; // 3 = FE, 4&5 = Loading screen, 6 = Gameplay
	IsOnFocus = !(*(bool*)_IsLostFocus);
	IsNotPaused = !(DALPauseStates_IsPaused());

	// Drunk Driver
	if ((GetAsyncKeyState(hotkeyAutoDrive) & 1) && (TheGameFlowManager == 6) && IsOnFocus && IsNotPaused) // When pressed "Drunk Driver" key
	{
		AutoDrive = !AutoDrive;

		if (AutoDrive)
		{
			Game_ForceAIControl(1);
		}
		else
		{
			Game_ClearAIControl(1);
		}
	}

	// Unlock All Things
	if ((GetAsyncKeyState(hotkeyUnlockAllThings) & 1) && IsOnFocus) // When pressed "Unlock All Things" key
	{
		UnlockAllThings = !UnlockAllThings;
		CIniReader iniReader("NFSUCExtraOptionsSettings.ini");
		iniReader.WriteInteger("Gameplay", "UnlockAllThings", UnlockAllThings);

		if (UnlockAllThings)
		{
			*(bool*)_UnlockAllThings = 1;
		}
		else
		{
			*(bool*)_UnlockAllThings = 0;
		}
	}

	// Debug Camera
	if (EnableDebugWorldCamera && (TheGameFlowManager == 6) && IsOnFocus && IsNotPaused)
	{
		if ((GetAsyncKeyState(VK_BACK) & 1))
		{
			DebugCamStatus = !DebugCamStatus;
			if (DebugCamStatus) CameraAI_SetAction(1, "CDActionDebug");
			else CameraAI_SetAction(1, "CDActionDrive");
		}

		if ((GetAsyncKeyState(VK_NEXT) & 1)) // Page Down : Toggle Debug Watch Car Camera
		{
			DebugWatchCarCamera = !DebugWatchCarCamera;
			*(unsigned char*)_mToggleCar = 1;

			if (DebugWatchCarCamera)
			{
				*(unsigned char*)_CameraDebugWatchCar = 1;
				CameraAI_SetAction(1, "CDActionDebugWatchCar");
			}

			else
			{
				CameraAI_SetAction(1, "CDActionDrive");
				*(unsigned char*)_CameraDebugWatchCar = 0;
			}
		}

		if ((GetAsyncKeyState(VK_ADD) & 1) && DebugWatchCarCamera) // + : Next car
		{
			*(unsigned char*)_mToggleCar += 1;
		}

		if ((GetAsyncKeyState(VK_SUBTRACT) & 1) && DebugWatchCarCamera) // - : Previous car
		{
			*(unsigned char*)_mToggleCar -= 1;
		}
	}

	// Freeze Camera
	if ((GetAsyncKeyState(hotkeyFreezeCamera) & 1) && IsOnFocus)
	{
		*(bool*)_Camera_StopUpdating = !(*(bool*)_Camera_StopUpdating);
	}

	// Ultimate Force Heat Level
	if ((GetAsyncKeyState(hotkeyToggleForceHeat) & 1) && (TheGameFlowManager == 6) && IsOnFocus && IsNotPaused) //When pressed "Toggle Force Heat"
	{
		forceHeatLevel = !forceHeatLevel; // Toggle option
		if (forceHeatLevel)
		{
			EnableHeatLevelOverride = 1;
			heatLevel = MinHeatLevel;
			if (ShowMessage) Hud_ShowMessage("^Ultimate Force Heat Level hack is enabled.", 0);
		}
		else
		{
			// Re-read the override boolean from config file
			CIniReader iniReader("NFSUCExtraOptionsSettings.ini");
			EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 1) == 1;
			if (ShowMessage) Hud_ShowMessage("^Ultimate Force Heat Level hack is disabled.", 0);
		}
	}

	if ((GetAsyncKeyState(hotkeyForceHeatLevel) & 1) && forceHeatLevel && (TheGameFlowManager == 6) && IsOnFocus && IsNotPaused) // Set Heat Level
	{

		heatLevel = (int)(floorf(heatLevel) - floorf(MinHeatLevel) + 1) % (int)(floorf(MaxHeatLevel) - floorf(MinHeatLevel) + 1) + MinHeatLevel;

		Game_SetWorldHeat(heatLevel); // Use direct function call to set the heat level
	}

	if ((GetAsyncKeyState(hotkeyToggleCops) & 1) && forceHeatLevel && (TheGameFlowManager == 6) && IsOnFocus) // Toggle Cops
	{
		ToggleCops = !ToggleCops;
		Game_SetCopsEnabled(ToggleCops);

		if (ToggleCops)
		{
			if (ShowMessage) Hud_ShowMessage("^Cops are now enabled.", 0);
		}
		else
		{
			if (ShowMessage) Hud_ShowMessage("^Cops are now disabled.", 0);
		}
	}


	// Cop Lights
	if ((GetAsyncKeyState(hotkeyToggleCopLights) & 1) && (TheGameFlowManager == 6) && IsOnFocus && IsNotPaused) // When pressed "Toggle Police Lights" key
	{
		copLightsEnabled = !copLightsEnabled;

		DWORD* PlayerPVehicle = GetPlayerPVehicle();

		if (PlayerPVehicle)
		{
			if (copLightsEnabled) // Enable cop lights - more proper method
			{
				if (!PVehicle_IsGlareOn(PlayerPVehicle, 0xF000)) PVehicle_GlareOn(PlayerPVehicle, 0xF000);
			}
			else // Disable cop lights
			{
				if (PVehicle_IsGlareOn(PlayerPVehicle, 0xF000)) PVehicle_GlareOff(PlayerPVehicle, 0xF000);
			}
		}
	}

	// Headlights
	if ((GetAsyncKeyState(hotkeyToggleHeadlights) & 1) && (TheGameFlowManager == 6) && IsOnFocus && IsNotPaused) // When pressed "Toggle Head Lights" key
	{
		DWORD* PlayerPVehicle = GetPlayerPVehicle();

		if (PlayerPVehicle)
		{
			if (!PVehicle_IsGlareOn(PlayerPVehicle, 7)) // Enable headlights
			{
				injector::WriteMemory<unsigned char>(0x6D1F74, 7, true); // sub_6D1F20
				injector::WriteMemory<int>(0x6D2021, 7, true); // sub_6D1F20
				injector::WriteMemory<int>(0x865C0A, 7, true); // CarRenderInfo::CreateCarLightFlares
				PVehicle_GlareOn(PlayerPVehicle, 7);
			}

			else // Disable headlights
			{
				injector::WriteMemory<unsigned char>(0x6D1F74, 0, true); // sub_6D1F20
				injector::WriteMemory<int>(0x6D2021, 0, true); // sub_6D1F20
				injector::WriteMemory<int>(0x865C0A, 0, true); // CarRenderInfo::CreateCarLightFlares
				PVehicle_GlareOff(PlayerPVehicle, 7);
			}
		}
	}

	// .hot Save And Load
	if (EnableSaveLoadHotPos && (TheGameFlowManager == 6) && IsOnFocus && IsNotPaused)
	{
		// Save
		if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(49) & 0x8000)
		{
			*(unsigned int*)_SaveHotPosition = 1;
			if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 1.", 0);
		}

		if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(50) & 0x8000)
		{
			*(unsigned int*)_SaveHotPosition = 2;
			if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 2.", 0);
		}

		if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(51) & 0x8000)
		{
			*(unsigned int*)_SaveHotPosition = 3;
			if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 3.", 0);
		}

		if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(52) & 0x8000)
		{
			*(unsigned int*)_SaveHotPosition = 4;
			if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 4.", 0);
		}

		if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(53) & 0x8000)
		{
			*(unsigned int*)_SaveHotPosition = 5;
			if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 5.", 0);
		}


		// Load
		if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(49) & 0x8000)
		{
			*(unsigned int*)_LoadHotPosition = 1;
			if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 1.", 0);
		}

		if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(50) & 0x8000)
		{
			*(unsigned int*)_LoadHotPosition = 2;
			if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 2.", 0);
		}

		if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(51) & 0x8000)
		{
			*(unsigned int*)_LoadHotPosition = 3;
			if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 3.", 0);
		}

		if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(52) & 0x8000)
		{
			*(unsigned int*)_LoadHotPosition = 4;
			if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 4.", 0);
		}

		if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(53) & 0x8000)
		{
			*(unsigned int*)_LoadHotPosition = 5;
			if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 5.", 0);
		}
	}

	_asm popad;
}