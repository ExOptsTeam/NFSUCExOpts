#pragma once

#include "stdio.h"
#include <windows.h>

// Function pointers
void(*Game_ForceAIControl)(int index) = (void(*)(int))0x663220;
void(*Game_ClearAIControl)(int index) = (void(*)(int))0x663290;
void(*Hud_ShowMessage)(char* MessageToShow, int script) = (void(*)(char*, int))0x661BB0;
void(*CameraAI_SetAction)(int EVIEW_ID, char* Action) = (void(*)(int, char*))0x4D2480;
bool(__thiscall* PVehicle_IsGlareOn)(DWORD* PVehicle, int VehicleFXID) = (bool(__thiscall*)(DWORD*, int))0x6EAFD0;
void(__thiscall* PVehicle_GlareOn)(DWORD* PVehicle, int VehicleFXID) = (void(__thiscall*)(DWORD*, int))0x6CC110;
void(__thiscall* PVehicle_GlareOff)(DWORD* PVehicle, int VehicleFXID) = (void(__thiscall*)(DWORD*, int))0x6CC120;
DWORD*(__cdecl* FE_Object_FindObject)(const char* pkg_name, DWORD obj_hash) = (DWORD*(__cdecl*)(const char*, DWORD))0x5859C0;
char* (__cdecl* EA_Localizer_LocalizerManager_GetPackedString)(DWORD stringHash, bool showLocalizationError) = (char*(__cdecl*)(DWORD, bool))0x586630;
DWORD(*bStringHash)(char* StringToHash) = (DWORD(*)(char*))0x4B3ED0;
bool(*DALPauseStates_IsPaused)() = (bool(*)())0x521960;
DWORD* (__thiscall* UCOM_Object_IList_Find)(DWORD* UCOM_Object_IList, char const* (__cdecl* iid)()) = (DWORD * (__thiscall*)(DWORD*, char const*(__cdecl*)()))0x5F6700;
char const* (__cdecl* IPerpetrator_IIDName)() = (char const* (__cdecl*)())0x402240;
void(*Game_SetCopsEnabled)(bool enabled) = (void(*)(bool))0x65C7C0;
void(*Game_ForcePursuitStart)(int minHeatLevel) = (void(*)(int))0x65C840;
void* (__thiscall* Attrib_Collection_GetData)(DWORD* Attrib_Collection, unsigned int attributeKey, unsigned int index) = (void* (__thiscall*)(DWORD*, unsigned int, unsigned int))0x4649B0;
void*(*Attrib_DefaultDataArea)(unsigned int bytes) = (void*(*)(unsigned int))0x676490;