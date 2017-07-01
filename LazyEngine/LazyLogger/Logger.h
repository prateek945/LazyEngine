#pragma once
#ifndef LOGGER_H_
#define LOGGER_H_
#include <stdio.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#include "../GeneralMacros/GeneralMacros.h"
namespace LE {
	class Logger {
	public:
		Logger();
		//~Logger();

		int Log(const char* format, ...);
		bool bIsActive;
	private:
		int DebugLog(const char* format, va_list arglist);
	};
};
#endif
