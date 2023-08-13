#pragma once


#include <string>
#include "game.h"

__interface IDatabase
{
public:
	bool WriteDataToFile(Game& game, std::string pathToSave, std::string databaseFileName, std::string databaseFileType);

	bool ReadDataFromFile(Game& game, std::string pathToSave, std::string databaseFileName, std::string databaseFileType);
};