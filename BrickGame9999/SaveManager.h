#pragma once

#include "Device.h"

class SaveManager
{
public:
	static void readSave(int &windowScale, int &framerateControl, Device &device);
	static void writeSave(int windowScale, int framerateControl, const Device &device);
	static void defaultSave(int windowScale, int framerateControl, const Device &device);

private:
	static const unsigned int magicVal = 0xFFFFFFFF;
	static unsigned int calcMagic(map<char, int> &highScore);
};