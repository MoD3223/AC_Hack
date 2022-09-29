#pragma once
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

using namespace std;


DWORD GetProcID(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, vector<unsigned int> offsets, unsigned int i);