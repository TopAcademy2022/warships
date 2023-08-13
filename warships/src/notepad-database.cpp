#include "notepad-database.h"

bool NotepadDatabase::WriteDataToFile(Game& game, std::string subdirectoryName, std::string databaseFileName, std::string databaseFileType)
{
	bool recordingResult = false;

	if (subdirectoryName[subdirectoryName.size() - 1] != '/')
	{
		subdirectoryName.push_back('/');
	}
	if (databaseFileType[0] != '.')
	{
		databaseFileType = '.' + databaseFileType;
	}

	try
	{
		if (this->_dataOfShip)
		{
			std::ofstream file = std::ofstream(subdirectoryName + databaseFileName + databaseFileType);
			file << this->_dataOfShip;
			file.close();

			recordingResult = true;
			delete this->_dataOfShip;
		}
	}
	catch (const std::exception ex)
	{
		// TODO: Save error to log file
		ex.what();
	}

	return recordingResult;
}

bool NotepadDatabase::ReadDataFromFile(Game& game, std::string subdirectoryName, std::string databaseFileName, std::string databaseFileType)
{
	bool recordingResult = false;

	if (subdirectoryName[subdirectoryName.size() - 1] != '/')
	{
		subdirectoryName.push_back('/');
	}
	if (databaseFileType[0] != '.')
	{
		databaseFileType = '.' + databaseFileType;
	}

	try
	{
		std::ifstream file = std::ifstream(subdirectoryName + databaseFileName + databaseFileType);
		this->_dataOfShip = nlohmann::json::parse(file);

		file.close();

		recordingResult = true;
	}
	catch (const std::exception ex)
	{
		// TODO: Save error to log file
		ex.what();
	}

	return recordingResult;
}