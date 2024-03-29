#include "stdio.h"
#include <windows.h>

#include "EALocalizerManager.h"

char* ExOptsTeamStr = "NFSUC Extra Options - �2022 ExOpts Team. No rights reserved.";
char newCopyrightStr[255];
char newEsrbStr[255];
bool IsTakeoverDoneOnce = 0;

void __fastcall FE_FESplashScreen_InitializeScreenAptFuncs(DWORD* _FESplashScreen, void* EDX_Unused)
{
	if (!IsTakeoverDoneOnce)
	{
		auto EACopyrightStr = EA_Localizer_LocalizerManager_GetPackedString(bStringHash("EA_LEGAL_LONG"), 0);
		sprintf(newCopyrightStr, "%s\n%s", EACopyrightStr, ExOptsTeamStr);
		EA_Localizer_LocalizerManager_SetString(bStringHash("EA_LEGAL_LONG"), newCopyrightStr);

		auto EALegalEsrbStr = EA_Localizer_LocalizerManager_GetPackedString(bStringHash("EA_LEGAL_ESRB"), 0);
		sprintf(newEsrbStr, "%s\n%s", "", EALegalEsrbStr);
		EA_Localizer_LocalizerManager_SetString(bStringHash("EA_LEGAL_ESRB"), newEsrbStr);

		IsTakeoverDoneOnce = 1;
	}
}