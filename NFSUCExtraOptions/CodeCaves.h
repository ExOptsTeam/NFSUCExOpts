#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

// 0x00647E17 @ GMW2Game::StartNewCareer
void __declspec(naked) StartingCashCodeCave()
{
	_asm
	{
		push [StartingCash]
		mov esi, ecx
		push 0x1776 // Cash

		push 0x647E20 // DALManager::SetInt...
		retn
	}
}

// 0x432E07 @ AIVehiclePerp::SetHeat
void __declspec(naked) ForceMaxHeatCodeCave_AIVehiclePerp_SetHeat()
{
	_asm
	{
		call Attrib_Collection_GetData
		test eax, eax
		jnz CheckOverride

		push 4
		call Attrib_DefaultDataArea
		add esp,4

		CheckOverride:
			cmp EnableHeatLevelOverride, 1
			jne dontforceMaxHeat

		forceMaxHeat :
			push ebx
			mov ebx, dword ptr ds: [_Tweak_ThreatRangeMax]
			mov dword ptr ds: [eax], ebx
			pop ebx

		dontforceMaxHeat :
			push 0x432E1A
			retn
	}
}

// 0x4440FA @ AIVehicleHuman::~AIVehicleHuman
void __declspec(naked) ForceMaxHeatCodeCave_AIVehicleHuman_dt()
{
	_asm
	{
		call Attrib_Collection_GetData
		test eax, eax
		jnz CheckOverride

		push 4
		call Attrib_DefaultDataArea
		add esp, 4

		CheckOverride:
			cmp EnableHeatLevelOverride, 1
			jne dontforceMaxHeat

		forceMaxHeat :
			push ebx
			mov ebx, dword ptr ds : [_Tweak_ThreatRangeMax]
			mov dword ptr ds : [eax] , ebx
			pop ebx

		dontforceMaxHeat :
			push 0x44410D
			retn
	}
}

// 0x69758A @ EBountyPointsGained::~EBountyPointsGained
void __declspec(naked) ForceMaxHeatCodeCave_EBountyPointsGained_dt()
{
	_asm
	{
		call Attrib_Collection_GetData
		test eax, eax
		jnz CheckOverride

		push 4
		call Attrib_DefaultDataArea
		add esp, 4

		CheckOverride:
			cmp EnableHeatLevelOverride, 1
			jne dontforceMaxHeat

		forceMaxHeat :
			push edx
			mov edx, dword ptr ds : [_Tweak_ThreatRangeMax]
			mov dword ptr ds : [eax] , edx
			pop edx

		dontforceMaxHeat : // 0x69759A ebp check skipped
			cmp ebp, dword ptr ds:[eax]
			add ebp, -1
			cmp ebp, 5
			jl originalcode

			mov ebp, 4 // fix oob

		originalcode:
			push 0x69759F // ... cost_to_state_for_heat_level
			retn
	}
}

// 0x41A8D4 @ AIVehicleCopCar::CheckForPursuitForHeat
void __declspec(naked) FixArrayOOBCodeCave_AIVehicleCopCar_CheckForPursuitForHeat()
{
	_asm
	{
		cmp eax, 5
		jl originalcode

		mov eax, 4

		originalcode:
			push eax
			push 0xFBCB42B2 //engage

			push 0x41A8DA
			retn
	}
}


// 0x41AA54 @ AIVehicleCopCar::CheckForPursuitForSpeed
void __declspec(naked) FixArrayOOBCodeCave_AIVehicleCopCar_CheckForPursuitForSpeed()
{
	_asm
	{
		cmp eax, 5
		jl originalcode

		mov eax, 4

		originalcode:
		push eax
			push 0xE24801 //engage_speeding

			push 0x41AA5A
			retn
	}
}

// 0x41ABCE @ AIVehicleCopCar::CheckForPursuitFor911Call
void __declspec(naked) FixArrayOOBCodeCave_AIVehicleCopCar_CheckForPursuitFor911Call()
{
	_asm
	{
		cmp eax, 5
		jl originalcode

		mov eax, 4

		originalcode:
		push eax
			push 0xA60BC171 //react_to_911_call 

			push 0x41ABD4
			retn
	}
}

// 0x438142 @ AICopManager::SpawnPatrolCar
void __declspec(naked) FixArrayOOBCodeCave_AICopManager_SpawnPatrolCar()
{
	_asm
	{
		cmp eax, 5
		jl originalcode

		mov eax, 4

		originalcode:
		push eax
			push 0xFA3F61A8 //search 

			push 0x438148
			retn
	}
}

