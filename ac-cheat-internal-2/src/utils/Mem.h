#pragma once

namespace Mem
{
	std::tuple<void*, DWORD> FindModuleBase(
		DWORD procId, const std::wstring& modName);
}