#include "Proc.h"



DWORD GetProcID(const wchar_t* procName) {

	DWORD procID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap,&procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procID = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap,&procEntry));
		}
	}
	return procID;
}

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName) {
	uintptr_t modBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap,&modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddress = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap,&modEntry));
		}


	}

	CloseHandle(hSnap);
	return modBaseAddress;
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, vector<unsigned int> offsets, unsigned int i) {
	//DMA = Dynamic Memory Allocation
		uintptr_t addressPointer = ptr;
		ReadProcessMemory(hProc, (BYTE*)addressPointer, &addressPointer, sizeof(addressPointer), 0);

		addressPointer += offsets[i];
		return addressPointer;

}