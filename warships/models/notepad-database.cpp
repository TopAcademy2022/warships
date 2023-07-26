#include "notepad-database.h"

bool NotepadDatabase::WriteDataToFile(Game& game, std::string subdirectoryName, std::string fileName, std::string fileType)
{
	bool result = false;

	try
	{
		if (this->_dataOfShip != '\0')
		{
			std::ofstream file = std::ofstream(subdirectoryName + "/" + fileName + "." + fileType);
			file << this->_dataOfShip;
			file.close();

			result = true;

			delete this->_dataOfShip;
		}
	}
	catch (const std::exception ex)
	{
		ex.what();
	}

	return result;
}

bool NotepadDatabase::ReadDataFromFile(Game& game, std::string subdirectoryName, std::string fileName, std::string fileType)
{
	bool result = false;
	try
	{
		std::ifstream file = std::ifstream(subdirectoryName + "/" + fileName + "." + fileType);
		file >> this->_dataOfShip;
		file.close();

		result = true;
	}
	catch (const std::exception ex)
	{
		ex.what();
	}

	return result;
}