#include <iostream>
#include <Windows.h>

using namespace std;

#include "BrickGame.h"

// main file for the program, runs Tetris

int main(int argc, char* argv[])
{
	try
	{
		BrickGame b;
		b.run();
	}
	catch (string ex)
	{
		MessageBox(nullptr, ex.c_str(), "Program failed", MB_ICONERROR | MB_OK);
	}

	return 0;
}