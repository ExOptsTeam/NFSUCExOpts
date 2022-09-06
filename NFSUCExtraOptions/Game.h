#include "stdio.h"
#include <windows.h>

#define UTL_ListableSet_IPlayer8_ePlayerList3_mLists_buckets1_mSize 0xDE99E4
#define UTL_ListableSet_IPlayer8_ePlayerList3_mLists_buckets1_mBegin 0xDE99DC

void Game_SetWorldHeat(float DesiredHeatLevel)
{
	int IPlayerCollectionSize = *(int*)UTL_ListableSet_IPlayer8_ePlayerList3_mLists_buckets1_mSize;
	if (IPlayerCollectionSize)
	{
		DWORD* IPlayerCollectionBegin = *(DWORD**)UTL_ListableSet_IPlayer8_ePlayerList3_mLists_buckets1_mBegin;
		if (IPlayerCollectionBegin)
		{
			DWORD* PlayerISimable = (DWORD*)(*(int(__thiscall**)(DWORD))(**(DWORD**)IPlayerCollectionBegin
				+ 4))(*(DWORD*)IPlayerCollectionBegin); // LocalPlayer_GetSimable(LocalPlayer*)

			if (PlayerISimable)
			{
				DWORD* PlayerPerp = UCOM_Object_IList_Find((DWORD*)PlayerISimable[1], IPerpetrator_IIDName);
				if (PlayerPerp)
				{
					(*(int(__thiscall**)(DWORD*, float))(*PlayerPerp + 8))(PlayerPerp, DesiredHeatLevel); // AIVehiclePerp_SetHeat(AIVehiclePerp*, float)
				}
			}
		}
	}
}