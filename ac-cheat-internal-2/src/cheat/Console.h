#pragma once

#include "module/Module.h"

namespace Console
{
	inline bool isAttached = false;

	bool Open();
	void Free();

	void PrintTitle();
	void Print(const Module& module);
	void PrintModules();
};