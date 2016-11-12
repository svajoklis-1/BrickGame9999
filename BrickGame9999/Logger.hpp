#pragma once

#include <Windows.h>
#include <cstdio>
#include <string>

class Logger
{
public:
	enum ForegroundColor;
	enum BackgroundColor;

	enum StatusLabel;

	struct Color {
		ForegroundColor fore;
		BackgroundColor back;
	};

	enum Tag;

	Logger();
	void log(const char *format, ...);
	void log(Logger::Tag tag, const char *format, ...);

	void logPartial(Logger::Tag tag, const char *format, ...);
	void logContinue(const char *format, ...);
	void logRight(int padding, const char *format, ...);

	void logLabel(Logger::StatusLabel label);

	void setColor(Color c);
	void setDefaultColor();

private:

	bool preLog();

	Color currentColor;
	Tag currentTag;
	bool partialInProgress = false;

	Color defaultColor;

	void _log(const char *format, va_list args, bool addEndl = true);

	void printHeader(Logger::Tag tag);
	

	const int ALL = 0b11111111;

	int logged;

	const char *tagToStr(Logger::Tag tag);
	const char *labelToStr(Logger::StatusLabel label);
	void setColorByTag(Logger::Tag tag);
	void setColorByStatusLabel(Logger::StatusLabel label);
	char *currentTime();
	HANDLE conHandle;

};

#include "Logger_types.hpp"

