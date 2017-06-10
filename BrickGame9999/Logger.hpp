#pragma once

#include <Windows.h>

class Logger
{
public:
	// Enum of available foreground colors mapped to Windows color values
	enum ForegroundColor;

	// Enum of available background colors mapped to Windows color values
	enum BackgroundColor;

	// Enum of left labels (INFO, DEBUG)
	enum Tag;

	// Available status (right) labels (OK, FAIL)
	enum StatusLabel;

	// Representation of a single color state of console
	struct Color {
		ForegroundColor fore;
		BackgroundColor back;
	};

	Logger();

	// Log with default DEBUG tag
	void log(const char *format, ...);

	// Log with a custom tag
	void log(Logger::Tag tag, const char *format, ...);

	// Start a partial log with label and initial message
	void logPartial(Logger::Tag tag, const char *format, ...);

	// Continue a partial log with text
	void logContinue(const char *format, ...);

	// Returns true when Logger is currently in the middle of logging a partial message
	bool inPartial() const { return partialInProgress; }

	// Logs a status label to the right and complete a partial log
	void logLabel(Logger::StatusLabel label);

	// Sets color of further Logger instructions
	void setColor(Color c);

	// Resets Logger color
	void setDefaultColor();

private:
	
	// Reset logger to inital state before any initial or complete log
	bool preLog();

	// Current color of Logger
	Color currentColor;

	// Current tag of Logger
	Tag currentTag;

	// Is a partial log in progress
	bool partialInProgress = false;

	// Default Logger color to reset to
	Color defaultColor;

	// Internal-use log method
	void _log(const char *format, va_list args, bool addEndl = true);

	// Prints the tag header for a log line
	void printHeader(Logger::Tag tag);
	
	// Mask containing all log tags
	const int ALL = 0b11111111;

	// Mask specifying which tags are to be logged
	int logged;

	// Convert a tag to string representation
	const char *tagToStr(Logger::Tag tag);

	// Convert a label to string representation
	const char *labelToStr(Logger::StatusLabel label);

	// Set color of tag label by tag
	void setColorByTag(Logger::Tag tag);

	// Set color of status label text by label
	void setColorByStatusLabel(Logger::StatusLabel label);

	// Retrieve current time in the format for Logger output
	char *currentTime();

	// Console handle for Logger output
	HANDLE conHandle;

	// Log on the right side of console with specified padding
	void logRight(int padding, const char *format, ...);

};

#include "Logger_types.hpp"

