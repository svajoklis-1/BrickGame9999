#include <iostream>
#include <Windows.h>

using namespace std;

#include "Tetris.h"

// main file for the program, runs Tetris

int main(int argc, char* argv[])
{
	Tetris t;

	try
	{
		t.run();
	}
	catch (string ex)
	{
		MessageBox(NULL, ex.c_str(), "Program failed", MB_ICONERROR | MB_OK);
	}

	return 0;
}