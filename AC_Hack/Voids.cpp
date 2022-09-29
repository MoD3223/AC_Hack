


void Write() {
	WriteProcessMemory(hProcess, (BYTE*)healthAddress, &newHealth, sizeof(newHealth), nullptr);
	WriteProcessMemory(hProcess, (BYTE*)armorAddress, &newArmor, sizeof(newArmor), nullptr);
	for (int i = 0; i < ammoOffeset.size(); i++)
	{
		uintptr_t ammoAddress = FindDMAAddy(hProcess, dynamicPointerBaseAddress, ammoOffeset, i);
		ReadProcessMemory(hProcess, (BYTE*)ammoAddress, &ammoValue, sizeof(ammoValue), nullptr);
		//Prevents crashing on suicide
		if (ammoValue < 30)
		{
			WriteProcessMemory(hProcess, (BYTE*)ammoAddress, &newAmmo, sizeof(newAmmo), nullptr);
		}
	}
}