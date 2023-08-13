#pragma once


#include "i-database.h"


class NotepadDatabase : public IDatabase
{
private:
	std::string _dataOfShip;

public:
	bool WriteDataToFile(Game& game, const std::string& subdirectoryName,
		const std::string& databaseFileName, const std::string& databaseFileType) override;

	bool ReadDataFromFile(Game& game, const std::string& subdirectoryName,
		const std::string& databaseFileName, const std::string& databaseFileType) override;
};
