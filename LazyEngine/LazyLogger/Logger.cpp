#include "Logger.h"
namespace LE {
	Logger::Logger() : bIsActive(true) {}
	int Logger::DebugLog(const char* format, va_list arglist) {
		static char s_buffer[MAX_DEBUG_CHAR];
		int charsWritten = vsnprintf(s_buffer, MAX_DEBUG_CHAR, format, arglist);
		OutputDebugString(s_buffer);
		return charsWritten;

	}

	int Logger::Log(const char* format, ...) {
		va_list argslist;
		va_start(argslist, format);
		int charsWritten = DebugLog(format, argslist);
		va_end(argslist);
		return charsWritten;
	}
};