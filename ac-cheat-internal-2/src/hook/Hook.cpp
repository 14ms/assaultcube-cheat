#include "pch.h"

#include "Hook.h"

static bool Detour32(uint8_t* src, uint8_t* dst, const uintptr_t len)
{
	if (len < 5) return false;

	DWORD curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	uintptr_t relativeAddress = (uintptr_t)(dst - (uintptr_t)src) - 5;

	*src = (char)'\xE9';
	*(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;

	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}

static uint8_t* TrampHook32(uint8_t* src, uint8_t* dst, const uintptr_t len)
{
	// Make sure the length is greater than 5
	if (len < 5) return 0;

	// Create the gateway (len + 5 for the overwritten bytes + the jmp)
	void* gateway = VirtualAlloc(0, len + 5,
		MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//Write the stolen bytes into the gateway
	memcpy_s(gateway, len, src, len);

	// Get the gateway to destination addy
	uintptr_t gatewayRelativeAddr = ((uintptr_t)src - (uintptr_t)gateway) - 5;

	// Add the jmp opcode to the end of the gateway
	*(uint8_t*)((uintptr_t)gateway + len) = (uint8_t)0xE9;

	// Add the address to the jmp
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;

	// Perform the detour
	Detour32(src, dst, len);

	return (uint8_t*)gateway;
}

Hook::Hook(uint8_t* src, uint8_t* dst, uint8_t* ptrToGatewayPtr, size_t length)
	: m_Src{ src }, m_Dst{ dst }, m_PtrToGatewayPtr{ ptrToGatewayPtr }, m_Length{ length }
{
}

Hook::Hook(const char* exportName, const char* moduleName,
	uint8_t* dst, uint8_t* ptrToGatewayPtr, size_t length)
	: m_Dst{ dst }, m_PtrToGatewayPtr{ ptrToGatewayPtr }, m_Length{ length }
{
	HMODULE mod = GetModuleHandleA(moduleName);

	// todo
	if (!mod)
	{
	}

	m_Src = (uint8_t*)GetProcAddress(mod, exportName);
}

void Hook::Enable()
{
	memcpy((void*)m_OriginalBytes, m_Src, m_Length);
	*(uintptr_t*)m_PtrToGatewayPtr = (uintptr_t)TrampHook32(m_Src, m_Dst, m_Length);
	m_Status = true;
}

void Hook::Disable()
{
	DWORD curProtection;

	VirtualProtect(m_Src, m_Length, PAGE_EXECUTE_READWRITE, &curProtection);
	memcpy(m_Src, (void*)m_OriginalBytes, m_Length);
	VirtualProtect(m_Src, m_Length, curProtection, &curProtection);
}

void Hook::Toggle()
{
	if (m_Status)
	{
		Enable();
	}
	else
	{
		Disable();
	}
}