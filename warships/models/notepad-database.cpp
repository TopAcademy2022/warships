#include "notepad-database.h"

bool NotepadDatabase::WriteDataToFile(std::string subdirectoryName, std::string fileName, std::string fileType)
{
	bool rezult = false;

	try
	{
		if (this->_dataOfShip != '\0')
		{
			std::ofstream file = std::ofstream(subdirectoryName + "/" + fileName + "." + fileType);
			file << this->_dataOfShip;
			file.close();

			rezult = true;

			delete this->_dataOfShip;
		}
	}
	catch (const std::exception ex)
	{
		ex.what();
	}

	return rezult;
}

bool NotepadDatabase::ReadDataFromFile(std::string subdirectoryName, std::string fileName, std::string fileType)
{
	bool rezult = false;
	try
	{
		std::ifstream file = std::ifstream(subdirectoryName + "/" + fileName + "." + fileType);
		file >> this->_dataOfShip;
		file.close();

		rezult = true;
	}
	catch (const std::exception ex)
	{
		ex.what();
	}

	return rezult;
}