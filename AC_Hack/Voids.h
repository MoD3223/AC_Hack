#pragma once
#include <iostream>
#include <vector>
#include "Proc.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <algorithm>


void WriteHealthArmor(uintptr_t healthAddress, int newHealth, uintptr_t armorAddress, int newArmor, DWORD procID, HANDLE hProcess);
void WriteAmmo(vector<unsigned int> ammoOffeset, int ammoValue, int newAmmo, uintptr_t dynamicPointerBaseAddress, HANDLE hProcess);
void AutoQuit(uintptr_t dynamicPointerBaseAddress);

class PlayerClass
{
public:
	//Constuctor
	PlayerClass(HANDLE hProcess,uintptr_t playerXAddressPointer, uintptr_t playerYAddressPointer,uintptr_t playerZAddressPointer) {
		playerX = ReadProcessMemory(hProcess, (BYTE*)playerXAddressPointer, &playerXAddressPointer, sizeof(playerXAddressPointer), nullptr);
		playerY = ReadProcessMemory(hProcess, (BYTE*)playerYAddressPointer, &playerYAddressPointer, sizeof(playerYAddressPointer), nullptr);
		playerZ = ReadProcessMemory(hProcess, (BYTE*)playerZAddressPointer, &playerZAddressPointer, sizeof(playerZAddressPointer), nullptr);
	}
	private:
	int playerHealth;
	int playerX;
	int playerY;
	int playerZ;
	float playerMagnitude;
};