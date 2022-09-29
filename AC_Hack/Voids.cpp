#include <iostream>
#include <vector>
#include "Proc.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <algorithm>
#include "Voids.h"



void WriteHealthArmor(uintptr_t healthAddress, int newHealth, uintptr_t armorAddress, int newArmor, DWORD procID, HANDLE hProcess) {
	hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, procID);
	WriteProcessMemory(hProcess, (BYTE*)healthAddress, &newHealth, sizeof(newHealth), nullptr);
	WriteProcessMemory(hProcess, (BYTE*)armorAddress, &newArmor, sizeof(newArmor), nullptr);
}

void WriteAmmo(vector<unsigned int> ammoOffeset, int ammoValue, int newAmmo, uintptr_t dynamicPointerBaseAddress, HANDLE hProcess) {


	for (int i = 0; i < ammoOffeset.size(); i++)
	{
		uintptr_t ammoAddress = FindDMAAddy(hProcess, dynamicPointerBaseAddress, ammoOffeset, i);
		ReadProcessMemory(hProcess, (BYTE*)ammoAddress, &ammoValue, sizeof(ammoValue), nullptr);
		//Prevents crashing on suicide or death
		if (ammoValue < 31)
		{
			WriteProcessMemory(hProcess, (BYTE*)ammoAddress, &newAmmo, sizeof(newAmmo), nullptr);
		}
	}

}

void AutoQuit(uintptr_t dynamicPointerBaseAddress)
{
	if (dynamicPointerBaseAddress == 0x17E0A8)
	{
		exit(0);
	}
}

void Aimbot(PlayerClass player) {

	while (true)
	{
		cout << "Current coordinates: " << player.playerX << " " << player.playerY << " " << player.playerZ << endl;
		Sleep(2);
	}
}


