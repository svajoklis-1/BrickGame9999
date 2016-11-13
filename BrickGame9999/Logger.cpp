#include "Logger.hpp"
#include <time.h>
#include <cstring>

Logger::Logger()
{
	defaultColor = { FG_LT_GRAY, BG_BLACK };
	currentColor = defaultColor;
	currentTag = Tag::DEBUG;
	conHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	logged = ALL;
}

bool Logger::preLog()
{
#ifdef DEBUG_9999
	// check if tag is to be logged
	if ((logged & currentTag) == 0)
	{
		return false;
	}

	if (partialInProgress)
	{
		partialInProgress = false;
		printf("\n");
	}

	setDefaultColor();

	return true;
#endif

	return false;
}

void Logger::log(const char *format, ...)
{
#ifdef DEBUG_9999
	currentTag = DEBUG;

	if (!preLog())
	{
		return;
	}

	va_list argptr;
	va_start(argptr, format);

	printHeader(currentTag);
	_log(format, argptr, true);

	va_end(argptr);
#endif
}

void Logger::log(Logger::Tag tag, const char *format, ...)
{
#ifdef DEBUG_9999
	currentTag = tag;

	if (!preLog())
	{
		return;
	}

	va_list argptr;
	va_start(argptr, format);

	printHeader(currentTag);
	_log(format, argptr, true);

	va_end(argptr);
#endif
}

void Logger::logPartial(Logger::Tag tag, const char *format, ...)
{
#ifdef DEBUG_9999

	currentTag = tag;

	if (!preLog())
	{
		return;
	}

	partialInProgress = true;

	va_list argptr;
	va_start(argptr, format);

	printHeader(currentTag);
	_log(format, argptr, false);

	va_end(argptr);
#endif
}

void Logger::logContinue(const char *format, ...)
{
#ifdef DEBUG_9999

	// check if tag is to be logged
	if ((logged & currentTag) == 0)
	{
		return;
	}

	if (!partialInProgress)
	{
		return;
	}

	va_list argptr;
	va_start(argptr, format);

	_log(format, argptr, false);

	va_end(argptr);

#endif
}

void Logger::logRight(int padding, const char *format, ...)
{
#ifdef DEBUG_9999

	// check if tag is to be logged
	if ((logged & currentTag) == 0)
	{
		return;
	}

	if (!partialInProgress)
	{
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(conHandle, &csbi);

	int rightWidth = padding;
	int currentPos = csbi.dwCursorPosition.X;
	int totalWidth = csbi.dwSize.X;
	int spaceCount = totalWidth - currentPos - rightWidth - 1;

	Color colorToPrint = currentColor;
	setDefaultColor();

	for (int i = 0; i < spaceCount; i++)
	{
		putchar(' ');
	}

	setColor(colorToPrint);

	va_list argptr;
	va_start(argptr, format);

	_log(format, argptr, false);

	va_end(argptr);

#endif
}

void Logger::_log(const char *format, va_list args, bool addEndl)
{
#ifdef DEBUG_9999

	vprintf(format, args);
	
	// "^cf0%s [%8s^cf0] ^c70My Text Here!"

	if (addEndl)
	{
		printf("\n");
	}

#endif
}

void Logger::printHeader(Logger::Tag tag)
{
	setColor({ FG_WHITE, BG_BLACK });

	char *currentTime = this->currentTime();
	printf("%s [", currentTime);
	delete currentTime;

	setColorByTag(tag);

	printf("%8s", tagToStr(tag));

	setColor({ FG_WHITE, BG_BLACK });
	printf("]");
	setColor(defaultColor);
	printf(" ");
}

void Logger::setColor(Color c)
{
	currentColor = c;
	SetConsoleTextAttribute(conHandle, c.fore | c.back);
}

void Logger::setDefaultColor()
{
	setColor(defaultColor);
}

const char *Logger::tagToStr(Logger::Tag tag)
{
	switch (tag) {
	case ERR:
		return "ERR";
	case WARN:
		return "WARN";
	case DEBUG:
		return "DEBUG";
	case ASSERT:
		return "ASSERT";
	case INFO:
		return "INFO";
	}

	return "MISSING";
}

const char *Logger::labelToStr(Logger::StatusLabel label)
{
	switch (label)
	{
	case OK:
		return "OK";
		break;
	case FAIL:
		return "FAIL";
		break;
	default:
		return "UNDEF";
		break;
	}
}

void Logger::logLabel(Logger::StatusLabel label)
{
	const char *text = labelToStr(label);
	int textLength = strlen(text);

	setDefaultColor();
	logRight(textLength + 2, "[");
	setColorByStatusLabel(label);
	logContinue(text);
	setDefaultColor();
	logContinue("]");
}

void Logger::setColorByTag(Logger::Tag tag)
{
	switch (tag)
	{
	case WARN:
		setColor({ FG_WHITE, BG_DK_YELLOW });
		break;
	case ERR:
		setColor({ FG_WHITE, BG_DK_RED });
		break;
	case DEBUG:
		setColor({ FG_CYAN, BG_BLACK });
		break;
	case ASSERT:
		setColor({ FG_WHITE, BG_DK_CYAN });
		break;
	case INFO:
		setColor({ FG_WHITE, BG_BLACK });
		break;
	default:
		setColor({ FG_WHITE, BG_BLACK });
		break;
	}
}

void Logger::setColorByStatusLabel(Logger::StatusLabel label)
{
	switch (label)
	{
	case OK:
		setColor({ FG_GREEN, BG_BLACK });
		break;

	case FAIL:
		setColor({ FG_RED, BG_BLACK });
		break;
	}
}

char *Logger::currentTime()
{
	char *time_buf = new char[16];
	time_t rawtime;
	time(&rawtime);
	struct tm *timeInfo;
	timeInfo = localtime(&rawtime);
	strftime(time_buf, 16, "%H:%M:%S", timeInfo);
	return time_buf;
}