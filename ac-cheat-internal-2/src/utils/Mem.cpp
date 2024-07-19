#include "pch.h"

#include "Mem.h"

//#define DEBUG

std::tuple<void*, DWORD> Mem::FindModuleBase(
	DWORD procId, const std::wstring& modName)
{
	const HANDLE modsSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procId);

	if (modsSnapshot == INVALID_HANDLE_VALUE)
	{
#ifdef DEBUG
		std::wcout << "[ERROR] Error while finding module '"
			<< modName << "', Code: " << GetLastError() << '\n';
#endif

		return { nullptr, GetLastError() };
	}

	MODULEENTRY32 modEntry = {};
	modEntry.dwSize = sizeof(MODULEENTRY32);

	BOOL success = Module32First(modsSnapshot, &modEntry);

	while (success)
	{
		if (modName.compare(modEntry.szModule) == 0)
		{
#ifdef DEBUG
			std::wcout << "[INFO] Found module '" << modName << "'\n";
#endif
			::CloseHandle(modsSnapshot);
			return { modEntry.modBaseAddr, 0 };
		}

		success = Module32Next(modsSnapshot, &modEntry);
	}

#ifdef DEBUG
	std::wcout << "[ERROR] Cannot find module '"
		<< modName << "'\n";
#endif

	::CloseHandle(modsSnapshot);
	return { nullptr, 0 };
}