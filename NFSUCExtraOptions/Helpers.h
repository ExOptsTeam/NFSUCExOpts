#pragma once

void ToggleHeatLevelOverride(bool Enabled)
{
	EnableHeatLevelOverride = Enabled;

	if (Enabled)
	{
		// Modify threat range tweaks (unused??)
		*(int*)_Tweak_ThreatRangeMin = (int)MinHeatLevel;
		*(int*)_Tweak_ThreatRangeMax = (int)MaxHeatLevel;
	}
	else
	{
		// Modify threat range tweaks (unused??)
		*(int*)_Tweak_ThreatRangeMin = 1;
		*(int*)_Tweak_ThreatRangeMax = 5;
	}
}

DWORD* GetPlayerPVehicle()
{
	DWORD* ISimableFromIPlayer, * ISimableFromIVehicle, * PlayerPVehicle;

	DWORD* PlayerIPlayer = *(DWORD**)_PlayerIPlayer; // Player 1
	int NumCurrentIVehicleElements = *(int*)0xDE93DC;

	for (int i = 0; i < NumCurrentIVehicleElements; i++)
	{
		PlayerPVehicle = *(DWORD**)(_PlayerPVehicle + i * 4);

		if (PlayerIPlayer) ISimableFromIPlayer = (*(DWORD * (__thiscall**)(DWORD*))(PlayerIPlayer[0] + 0x4))(PlayerIPlayer); // RecordablePlayer::GetSimable
		else ISimableFromIPlayer = 0;
		if (PlayerPVehicle) ISimableFromIVehicle = (*(DWORD * (__thiscall**)(DWORD*))(PlayerPVehicle[0] + 0x4))(PlayerPVehicle); // PVehicle::GetSimable
		else ISimableFromIVehicle = 0;

		if (ISimableFromIPlayer && ISimableFromIVehicle && (ISimableFromIPlayer == ISimableFromIVehicle)) return PlayerPVehicle;
	}

	return 0;
}

int Return0Hook()
{
	return 0;
}

float Return0fHook()
{
	return 0.0f;
}