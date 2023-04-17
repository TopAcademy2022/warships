#pragma once


#include "i-database.h"
#include <fstream>

class NotepadDatabase : public IDatabase
{
private:
	char* _dataOfShip;

public:
	bool WriteDataToFile(std::string subdirectoryName, std::string fileName, std::string fileType);

	bool ReadDataFromFile(std::string subdirectoryName, std::string fileName, std::string fileType);
};