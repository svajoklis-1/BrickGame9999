#pragma once

#include <Windows.h>

class Logger
{
public:
	// enum of available foreground colors mapped to Windows color values
	enum ForegroundColor;

	// enum of available background colors mapped to Windows color values
	enum BackgroundColor;

	// enum of left labels (INFO, DEBUG)
	enum Tag;

	// available status (right) labels
	enum StatusLabel;

	// representation of a single color state of console
	struct Color {
		ForegroundColor fore;
		BackgroundColor back;
	};

	Logger();

	// log with default DEBUG tag
	void log(const char *format, ...);

	// log with a custom tag
	void log(Logger::Tag tag, const char *format, ...);

	// start a partial log with label and initial message
	void logPartial(Logger::Tag tag, const char *format, ...);

	// continue a partial log with text
	void logContinue(const char *format, ...);

	// returns true when Logger is currently in the middle of logging a partial message
	bool inPartial() const { return partialInProgress; }

	// logs a status label to the right
	void logLabel(Logger::StatusLabel label);

	// sets color of further Logger instructions
	void setColor(Color c);

	// resets Logger color
	void setDefaultColor();

private:
	
	// reset logger to inital state before any initial or complete log
	bool preLog();

	// current color of Logger
	Color currentColor;

	// current tag of Logger
	Tag currentTag;

	// is a partial log in progress
	bool partialInProgress = false;

	// default Logger color to reset to
	Color defaultColor;

	// internal-use log method
	void _log(const char *format, va_list args, bool addEndl = true);

	// prints the tag header for a log line
	void printHeader(Logger::Tag tag);
	
	// mask containing all log tags
	const int ALL = 0b11111111;

	// mask specifying which tags are to be logged
	int logged;

	// convert a tag to string representation
	const char *tagToStr(Logger::Tag tag);

	// convert a label to string representation
	const char *labelToStr(Logger::StatusLabel label);

	// set color of tag label by tag
	void setColorByTag(Logger::Tag tag);

	// set color of status label text by label
	void setColorByStatusLabel(Logger::StatusLabel label);

	// retrieve current time in the format for Logger output
	char *currentTime();

	// console handle for Logger output
	HANDLE conHandle;

	// log on the right side of console with specified padding
	void logRight(int padding, const char *format, ...);

};

#include "Logger_types.hpp"

