#pragma once

#include <Windows.h>
#include <cstdio>
#include <string>

class Logger
{
public:
	enum Tag;

	Logger();
	void log(const char *format, ...);
	void log(Logger::Tag tag, const char *format, ...);

	void logPartial(Logger::Tag tag, const char *format, ...);
	void logRight(const char *format, ...);

	void assrt(bool condition, const char *format, ...);

private:

	void log(Logger::Tag tag, const char *format, va_list args, bool addEndl = true);

	const int ALL = 0b11111111;

	int logged;

	const char *parseFormat(const char *format, va_list args);

	struct Color;

	void setColor(Color c);
	const char *tagToStr(Logger::Tag tag);
	void setColorByTag(Logger::Tag tag);
	char *currentTime();
	HANDLE conHandle;

	enum ForegroundColor;
	enum BackgroundColor;

	struct Color {
		ForegroundColor fore;
		BackgroundColor back;
	};
};

#include "Logger_types.h"