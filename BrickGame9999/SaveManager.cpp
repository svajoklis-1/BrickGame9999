#include <iostream>
#include <map>
#include <boost/foreach.hpp>
#include <boost/property_tree/ini_parser.hpp>
using namespace std;
namespace pt = boost::property_tree;

#include "SaveManager.hpp"
#include "Global.hpp"

void SaveManager::readSave(int &windowScale, int &framerateControl, Device &device)
{
	pt::ptree saveFile;

	unsigned int magic;

	try
	{
		pt::read_ini("saveData.ini", saveFile);
		magic = saveFile.get<unsigned int>("magic.magic", magicVal);

		windowScale = saveFile.get<int>("window.scale", 1);
		framerateControl = saveFile.get<int>("window.frameControl", 2);

		device.speaker.setMuted(saveFile.get<int>("device.muted", 0) == 1);

		device.setBGCount(saveFile.get<int>("device.backgroundCount", 14));
		device.setBG(saveFile.get<int>("device.currentBackground", 1) - 1);

		try
		{
			BOOST_FOREACH(auto &v, saveFile.get_child("highScore"))
			{
				device.highScore[v.first.c_str()[0]] = v.second.get_value<int>();
			}
		}
		catch (...)
		{
			l.log(Logger::WARN, "HighScore file not found!");
		}

	}
	catch (...)
	{
		defaultSave(windowScale, framerateControl, device);
		throw string("saveData read failed, reverting to defaults...\nRestart and try again");
	}

	if (magic != calcMagic(device.highScore))
	{
		defaultSave(windowScale, framerateControl, device);
		throw string("saveData corrupted, reverting...\nRestart and try again");
	}
}

unsigned int SaveManager::calcMagic(map<char,int> &highScore)
{
	unsigned int magic = magicVal;

	for (auto iterator = highScore.begin(); iterator != highScore.end(); ++iterator)
	{
		if (static_cast<unsigned>(iterator->second) != 0)
			magic ^= static_cast<unsigned>(iterator->second);
	}

	return magic;
}

void SaveManager::writeSave(int windowScale, int framerateControl, const Device &device)
{
	pt::ptree saveFile;
	pt::read_ini("saveData.ini", saveFile);

	saveFile.put("window.scale", windowScale);
	saveFile.put("window.frameControl", framerateControl);

	saveFile.put("device.muted", device.speaker.isMuted() ? 1 : 0);

	saveFile.put("device.currentBackground", device.getCurrentBG() + 1);

	auto highScores = device.getHighScores();
	for (auto iterator = highScores.begin(); iterator != highScores.end(); ++iterator)
	{
		string key;
		key.append("highScore.");
		key.push_back(iterator->first);
		saveFile.put<int>(key, device.getHighScores()[iterator->first]);
	}

	saveFile.put("magic.magic", calcMagic(device.getHighScores()));

	pt::write_ini("saveData.ini", saveFile);
}

void SaveManager::defaultSave(int windowScale, int framerateControl, const Device &device)
{
	pt::ptree saveFile;

	saveFile.put("window.scale", windowScale);
	saveFile.put("window.frameControl", framerateControl);

	saveFile.put("device.backgroundCount", device.getBGCount());
	saveFile.put("device.currentBackground", device.getCurrentBG() + 1);

	pt::write_ini("saveData.ini", saveFile);
}