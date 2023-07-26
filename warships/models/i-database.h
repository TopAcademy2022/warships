#pragma once

#include <string>
#include "game.h"

__interface IDatabase
{
public:
	bool WriteDataToFile(Game& game, std::string pathToSave, std::string fileName, std::string fileType);

	bool ReadDataFromFile(Game& game, std::string pathToSave, std::string fileName, std::string fileType);
};