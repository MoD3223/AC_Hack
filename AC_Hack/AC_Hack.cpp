﻿// AC_Hack.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>
#include "Proc.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <algorithm>
#include "Voids.h"

using namespace std;
/*
//Book

template<typename T>
DWORD protectMemory(HANDLE proc, LPVOID adr, DWORD prot) {
	DWORD oldProt;
	VirtualProtectEx(proc, adr, sizeof(T), prot, &oldProt);
	return oldProt;
}

template<typename T>
T readMemory(HANDLE proc, LPVOID adr) {
	T val;
	ReadProcessMemory(proc, adr, &val, sizeof(T), NULL);
	return val;
}
template<typename T>
void writeMemory(HANDLE proc, LPVOID adr, T val) {
	WriteProcessMemory(proc, adr, &val, sizeof(T), NULL);
}

void forceWrite() {
	protectMemory<DWORD>(process, address, PAGE_READWRITE);
	writeMemory<DWORD>(process, address, newValue);


	DWORD oldProt = protectMemory<DWORD>(process, address, PAGE_READWRITE);
	writeMemory<DWORD>
}

*/

int main()
{
	//Get ProcID
	DWORD procID = GetProcID(L"ac_client.exe");


	//GetModuleBase Address
	uintptr_t moduleBase = GetModuleBaseAddress(procID, L"ac_client.exe");


	//Get Handle to process (using OpenProcess)
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, procID);
	//hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	//Resolve base address of the pointer chain

	//Module base = ac_client.exe, 0x17E0A8 taken from pointer to health;
	uintptr_t dynamicPointerBaseAddress = moduleBase + 0x17E0A8;

	cout << "Dynamic Pointer Base Address == 0x" << hex << dynamicPointerBaseAddress << endl;
	AutoQuit(dynamicPointerBaseAddress);

	//Resolve pointer chain

	//Offsets to add from cheatengine, for health it's EC;
	//vector<unsigned int> ammoOffeset = { 0x374, 0x14, 0x0};
	vector<unsigned int> healthOffset = { 0xEC };
	vector<unsigned int> ammoOffeset = { 0x140,0x11C,0x138,0x114,0x13C,0x118,0x134,0x110,0x130,0x10C,0x144,0x12C,0x108 };
	vector<unsigned int> armorOffset = { 0xF0 };
	//TO FILL
	vector<unsigned int> playerXOffset = { 0x00 };
	vector<unsigned int> playerYOffset = { 0x00 };
	vector<unsigned int> playerZOffset = { 0x00 };
	uintptr_t playerXAddressPointer = FindDMAAddy(hProcess, dynamicPointerBaseAddress, playerXOffset, 0);
	uintptr_t playerYAddressPointer = FindDMAAddy(hProcess, dynamicPointerBaseAddress, playerYOffset, 0);
	uintptr_t playerZAddressPointer = FindDMAAddy(hProcess, dynamicPointerBaseAddress, playerZOffset, 0);

	uintptr_t healthAddress = FindDMAAddy(hProcess, dynamicPointerBaseAddress, healthOffset, 0);
	uintptr_t armorAddress = FindDMAAddy(hProcess, dynamicPointerBaseAddress, armorOffset, 0);
	//cout << "Ammo Address == 0x" << hex << ammoAddress << endl;

	//Read value
	//int ammoValue = 0;
	//ReadProcessMemory(hProcess, (BYTE*)ammoAddress, &ammoValue, sizeof(ammoValue), nullptr);
	//cout << "Current ammo = " << dec << ammoValue << endl;



	//Write to it
	WriteHealthArmor(healthAddress, 9999, armorAddress, 100,procID,hProcess);
	WriteAmmo(ammoOffeset, 0, 101, dynamicPointerBaseAddress, hProcess);


	//Read again
	//ReadProcessMemory(hProcess, (BYTE*)ammoAddress, &ammoValue, sizeof(ammoValue), nullptr);

	//cout << "New ammo = " << dec << ammoValue << endl;



	//Aimbot+WH

	PlayerClass LocalPlayer(hProcess, playerXAddressPointer, playerYAddressPointer, playerZAddressPointer);





	getchar();
	return 0;

}