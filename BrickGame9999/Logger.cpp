#include "Logger.h"
#include <time.h>
#include <cstring>

Logger::Logger()
{
	conHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	logged = ALL;
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

void Logger::assrt(bool condition, const char *format, ...)
{
#ifdef DEBUG_9999
	va_list argptr;
	va_start(argptr, format);
	if (!condition)
	{
		log(ASSERT, format, argptr);
	}
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

	char *currentTime = this->currentTime();
	printf("%s [", currentTime);
	delete currentTime;

	setColorByTag(tag);

	printf("%8s", tagToStr(tag));

	setColor(FG_WHITE, BG_BLACK);
	printf("]");
	setColor(FG_LT_GRAY, BG_BLACK);
	printf(" ");

	const char *parsedFormat = parseFormat(format, args);

	printf(parsedFormat);

	delete[] parsedFormat;

	printf("\n");

#endif
}

const char *Logger::parseFormat(const char *format, va_list args)
{
	char *printedFormat = new char[1024];

	vsprintf(printedFormat, format, args);

	char *parsedFormat = new char[1024];

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(conHandle, &csbi);

	int formatLength = strlen(printedFormat);
	
	int i = 0;
	int pi = 0;
	while (i < formatLength)
	{
		if (i <= formatLength - 2) {
			if (printedFormat[i] == '^' && printedFormat[i + 1] == 'r')
			{
				int rightWidth = formatLength - (i + 2);
				int currentPos = csbi.dwCursorPosition.X;
				int totalWidth = csbi.dwSize.X;
				int spaceCount = totalWidth - currentPos - rightWidth - pi - 1;

				while (spaceCount > 0)
				{
					parsedFormat[pi] = ' ';
					pi++;
					spaceCount--;
				}

				i += 2;
				continue;
			}
		}

		parsedFormat[pi] = printedFormat[i];
		i++;
		pi++;
	}

	parsedFormat[pi] = '\0';

	delete[] printedFormat;

	return parsedFormat;
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
	case ASSERT:
		return "ASSERT";
	case INFO:
		return "INFO";
	}

	return "MISSING";
}

void Logger::setColorByTag(Logger::Tag tag)
{
	switch (tag)
	{
	case WARN:
		setColor(FG_WHITE, BG_DK_YELLOW);
		break;
	case ERR:
		setColor(FG_WHITE, BG_DK_RED);
		break;
	case DEBUG:
		setColor(FG_CYAN, BG_BLACK);
		break;
	case ASSERT:
		setColor(FG_WHITE, BG_DK_CYAN);
		break;
	case INFO:
		setColor(FG_WHITE, BG_BLACK);
		break;
	default:
		setColor(FG_WHITE, BG_BLACK);
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