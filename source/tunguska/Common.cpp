#include "Common.h"
#include <stdio.h>
#include <stdarg.h>

void PrintWithArgs(LogVerbosity verbosity, const char* format, va_list args)
{
	switch (verbosity)
	{
	case LogVerbosity::Info:
		fprintf(stdout, "[INFO]    ");
		break;
	case LogVerbosity::Warning:
		fprintf(stdout, "[WARNING] ");
		break;
	case LogVerbosity::Error:
		fprintf(stdout, "[ERROR]   ");
		break;
	}

	vfprintf(stdout, format, args);

	fprintf(stdout, "\n");
}

void Log::Print(LogVerbosity verbosity, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	PrintWithArgs(verbosity, format, args);
	va_end(args);
}

void Log::Print(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	PrintWithArgs(LogVerbosity::Info, format, args);
	va_end(args);
}

void Log::Warning(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	PrintWithArgs(LogVerbosity::Warning, format, args);
	va_end(args);
}

void Log::Error(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	PrintWithArgs(LogVerbosity::Error, format, args);
	va_end(args);
}