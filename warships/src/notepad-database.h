#pragma once


#include <fstream>
#include <nlohmann/json.hpp>
#include "i-database.h"

class NotepadDatabase : public IDatabase
{
private:
	nlohmann::json _dataOfShip;

public:
	bool WriteDataToFile(Game& game, std::string subdirectoryName, std::string databaseFileName, std::string databaseFileType);

	bool ReadDataFromFile(Game& game, std::string subdirectoryName, std::string databaseFileName, std::string databaseFileType);
};