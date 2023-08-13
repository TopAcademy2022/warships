#pragma once


#include <string>
#include "game.h"

class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool WriteDataToFile(Game& game, const std::string& pathToSave,
		const std::string& databaseFileName, const std::string& databaseFileType) = 0;

	virtual bool ReadDataFromFile(Game& game, const std::string& pathToSave,
		const std::string& databaseFileName, const std::string& databaseFileType) = 0;
};
