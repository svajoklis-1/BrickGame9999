#pragma once

#include "Device.hpp"

class SaveManager
{
public:
	// Read save from the default save file
	static void readSave(int &windowScale, int &framerateControl, Device &device);

	// Write save to the default save file
	static void writeSave(int windowScale, int framerateControl, const Device &device);

	// Write default save file values to the save file
	static void defaultSave(int windowScale, int framerateControl, const Device &device);

private:
	// Seed magic value to be used in the magic-protection calculation
	static const unsigned int magicVal = 0xFFFFFFFF;

	// Calculate magic value by high-score values
	static unsigned int calcMagic(map<char, int> &highScore);
};