#pragma once

struct Hook
{
	bool m_Status = false;

	uint8_t* m_Src = nullptr;
	uint8_t* m_Dst = nullptr;
	uint8_t* m_PtrToGatewayPtr = nullptr;

	size_t m_Length = 0;
	uint8_t m_OriginalBytes[10] = { 0 };

	Hook(uint8_t* src, uint8_t* dst, uint8_t* ptrToGatewayPtr, size_t length);
	Hook(const char* exportName, const char* moduleName,
		uint8_t* dst, uint8_t* ptrToGatewayPtr, size_t length);

	void Enable();
	void Disable();
	void Toggle();
};