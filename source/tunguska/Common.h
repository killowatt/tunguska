#pragma once

typedef signed int int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

struct NonCopyable
{
	NonCopyable& operator=(const NonCopyable&) = delete;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable() = default;
};

enum class LogVerbosity
{
	Info,
	Warning,
	Error
};

class Log
{
public:
	static void Print(LogVerbosity verbosity, const char* format, ...);
	static void Print(const char* format, ...);
	static void Warning(const char* format, ...);
	static void Error(const char* format, ...);
};