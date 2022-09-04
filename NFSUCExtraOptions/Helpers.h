#pragma once

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