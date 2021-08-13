#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

#define _EA_Memcard_NFSMemcardInterface_sInstance 0xD996EC

char const* EA_Memcard_IMemcardFile_GetFilename()
{
	// Force Name
	if (strcmp(PlayerName, "0") != 0)
	{
		return PlayerName;
	}
	// Use the profile name instead
	DWORD* MemCardsInstance = (DWORD*)*(DWORD*)_EA_Memcard_NFSMemcardInterface_sInstance;
	if (!MemCardsInstance) return 0;
	MemCardsInstance = (DWORD*)MemCardsInstance[1];
	if (!MemCardsInstance) return 0;
	return (char const*)MemCardsInstance + 0x14;
}