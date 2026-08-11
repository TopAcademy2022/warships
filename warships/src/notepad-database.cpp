#include "notepad-database.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype> 

namespace
{
	std::string GetFileExtension(const std::string& fileName)
	{
		size_t dotPos = fileName.find_last_of('.');
		if (dotPos == std::string::npos || dotPos == 0 || dotPos == fileName.length() - 1)
		{
			return std::string();
		}
		return fileName.substr(dotPos + 1);
	}

	std::string BuildFilePath(const std::string& subdirectoryName,
		const std::string& databaseFileName, const std::string& databaseFileType)
	{
		if (databaseFileName.empty())
		{
			return std::string();
		}

		std::string path = subdirectoryName;
		if (!path.empty() && path.back() != '/' && path.back() != '\\')
		{
			path.push_back('/');
		}

		path += databaseFileName;
		if (!databaseFileType.empty())
		{
			if (databaseFileType.front() != '.')
			{
				path.push_back('.');
			}
			path += databaseFileType;
		}

		return path;
	}

	std::string SerializeGame(const Game& game)
	{
		std::ostringstream data;
		data << "elapsed-seconds " << game.GetLastTime() << '\n';

		unsigned int battlefieldNumber = 1;
		for (const battlefield::Battlefield& currentBattlefield : game.GetBattlefields())
		{
			data << "battlefield " << battlefieldNumber++ << '\n';
			for (const logic::Ship& ship : currentBattlefield.GetShips())
			{
				data << "ship " << static_cast<unsigned int>(ship.GetShipType());
				for (const logic::Cell& deck : ship.GetDecks())
				{
					data << ' ' << deck.GetPositionX() << ',' << deck.GetPositionY()
						<< ',' << (deck.GetIsHit() ? 1 : 0);
				}
				data << '\n';
			}
		}

		return data.str();
	}
}

bool NotepadDatabase::WriteDataToFile(Game& game, const std::string& subdirectoryName,
	const std::string& databaseFileName, const std::string& databaseFileType)
{
	const std::string filePath = BuildFilePath(subdirectoryName, databaseFileName, databaseFileType);
	if (filePath.empty())
	{
		return false;
	}

	this->_dataOfShip = SerializeGame(game);
	std::ofstream file(filePath, std::ios::out | std::ios::trunc);
	if (!file)
	{
		return false;
	}

	file << this->_dataOfShip;
	return file.good();
}

bool NotepadDatabase::ReadDataFromFile(Game& game, const std::string& subdirectoryName,
	const std::string& databaseFileName, const std::string& databaseFileType)
{
	(void)game;
	const std::string filePath = BuildFilePath(subdirectoryName, databaseFileName, databaseFileType);
	if (filePath.empty())
	{
		return false;
	}

	std::ifstream file(filePath);
	if (!file)
	{
		return false;
	}

	std::ostringstream data;
	data << file.rdbuf();
	if (file.bad())
	{
		return false;
	}

	this->_dataOfShip = data.str();
	return true;
}
