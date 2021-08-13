#include "stdio.h"
#include <windows.h>

#define EA_Localizer_LocalizerManager_mPriorityMap 0xD98264

void EA_Localizer_LocalizerManager_SetString(unsigned int stringHash, char const* Text)
{
    int TopLangPack; // ebx
    char* result; // eax
    int count; // esi
    DWORD* LangPack; // edi
    DWORD* PriMap; // edi

    PriMap = *(DWORD**)EA_Localizer_LocalizerManager_mPriorityMap;
    
    if (PriMap)
    {
        int LangPackID = PriMap[0]; // mDbID
        LangPack = (DWORD*)PriMap[1]; // mLangPack
        if ((LangPackID != -1) && LangPack)
        {
            int CategoryCount = LangPack[0];
            int MaxCategories = LangPack[1];
            DWORD* Categories = (DWORD*)LangPack[2];
            if (Categories)
            {
                for (int i = 0; i < MaxCategories; i++)
                {
                    if (i > CategoryCount) break;
                    int NumberOfStringRecords = Categories[i * 7 + 4];
                    DWORD* RecordTable = (DWORD*)Categories[i * 7 + 6];
                    if (RecordTable)
                    {
                        for (int r = 0; r < NumberOfStringRecords; r++)
                        {
                            if (RecordTable[r * 2] == stringHash)
                            {
                                RecordTable[r * 2 + 1] = (DWORD)Text;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}