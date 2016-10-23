#include "Logger.h"

Logger::Logger()
{
	conHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	logged = DEBUG | ERR | WARN;
}

void Logger::log(const char *format, ...)
{
#ifdef DEBUG_9999
	va_list argptr;
	va_start(argptr, format);
	log(DEBUG, format, argptr);
	va_end(argptr);
#endif
}

void Logger::log(Logger::Tag tag, const char *format, ...)
{
#ifdef DEBUG_9999
	va_list argptr;
	va_start(argptr, format);
	log(tag, format, argptr);
	va_end(argptr);
#endif
}

void Logger::log(Logger::Tag tag, const char *format, va_list args)
{
#ifdef DEBUG_9999

	// check if tag is to be logged
	if ((logged & tag) == 0)
	{
		return;
	}

	setColor(FG_WHITE, BG_BLACK);
	printf("[");

	switch (tag)
	{
	case WARN:
		setColor(FG_WHITE, BG_DK_YELLOW);
		break;
	case ERR:
		setColor(FG_WHITE, BG_DK_RED);
		break;
	case DEBUG:
		setColor(FG_WHITE, BG_BLUE);
		break;
	}

	printf("%s", tagToStr(tag));

	setColor(FG_WHITE, BG_BLACK);
	printf("]");
	setColor(FG_LT_GRAY, BG_BLACK);
	printf(" ");

	vprintf(format, args);

	printf("\n");

#endif
}

void Logger::setColor(int fore, int back)
{
	SetConsoleTextAttribute(conHandle, fore | back);
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
	}

	return "MISSING";
}