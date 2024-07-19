#include "pch.h"

#include "src/hook/Hook.h"

#include "src/utils/Drawing.h"

#include "src/cheat/Cheat.h"
#include "src/cheat/module/Modules.h"

typedef BOOL(__stdcall* t_GlSwapBuffers)(HDC hdc);
static t_GlSwapBuffers glSwapBuffersGateway = nullptr;

static BOOL __stdcall hk_GlSwapBuffers(HDC hdc)
{
	InputSystem::Instance().UpdateKeyStates();

	if (Cheat::isStopping)
	{
		return glSwapBuffersGateway(hdc);
	}

	Drawing::SetupOrtho();
	Modules::UpdateModules();
	Drawing::RestoreGL();

	return glSwapBuffersGateway(hdc);
}

static DWORD WINAPI CheatThread(LPVOID hModule)
{
	if (!Cheat::Start())
	{
		FreeLibraryAndExitThread((HMODULE)hModule, 0);
		return 0;
	}

	Hook swapBuffersHook = { "wglSwapBuffers", "opengl32.dll",
		(uint8_t*)hk_GlSwapBuffers, (uint8_t*)&glSwapBuffersGateway, 5 };
	swapBuffersHook.Enable();

	while (!Cheat::isStopping)
	{
		Sleep(1000);
	}

	swapBuffersHook.Disable();
	Cheat::Stop();

	FreeLibraryAndExitThread((HMODULE)hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, CheatThread, hModule, 0, nullptr);
	}
	else if (reason == DLL_PROCESS_DETACH)
	{
	}
	
	return TRUE;
}