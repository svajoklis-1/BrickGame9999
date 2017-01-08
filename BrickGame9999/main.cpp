#include <iostream>
#include <Windows.h>

using namespace std;

#include "BrickGame.hpp"
#include "Logger.hpp"
#include "Global.hpp"

#ifdef TEST_9999
#include "Test_Runner.hpp"
#endif

// main file for the program, runs Tetris
// catches all string exceptions
// catches all exceptions when not in debug

int main(int argc, char* argv[])
{
#ifndef TEST_9999

	try
	{
		BrickGame b;
		b.run();
}
	catch (string ex)
	{
		l.log(Logger::ERR, ex.c_str());
		MessageBox(nullptr, ex.c_str(), "Program failed", MB_ICONERROR | MB_OK);
	}
#ifndef DEBUG_9999
	catch (...)
	{
		MessageBox(nullptr, "Uncaught exception", "Program failed", MB_ICONERROR | MB_OK);
	}
#endif

	l.log(Logger::INFO, "Brick Game ended its run.");
	printf("Press any key to continue...");
	getchar();

	return 0;

#else

	Test::Runner testRunner;

	try
	{
		testRunner.run();
	}
	catch (string ex)
	{
		l.log(Logger::ERR, "Invalid test state: %s", ex.c_str());
	}

	printf("\nPress any key to continue...");
	getchar();

	return 0;

#endif

}