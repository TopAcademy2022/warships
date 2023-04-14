#pragma once


#include <string>

__interface IDatabase
{
public:
	bool WriteDataToFile(std::string subdirectoryName, std::string fileName, std::string fileType);

	bool ReadDataFromFile(std::string subdirectoryName, std::string fileName, std::string fileType);
};