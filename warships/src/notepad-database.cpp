#include "notepad-database.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <regex>
#include <memory>

namespace
{
    std::string ToLower(const std::string& str)
    {
        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return lower;
    }

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
            std::string cleanType = databaseFileType;
            if (cleanType.front() == '.')
            {
                cleanType = cleanType.substr(1);
            }

            std::string existingExtension = GetFileExtension(databaseFileName);

            if (existingExtension.empty() || ToLower(existingExtension) != ToLower(cleanType))
            {
                if (databaseFileType.front() != '.')
                {
                    path.push_back('.');
                }
                path += cleanType;
            }
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

    struct ParsedDeck
    {
        unsigned int x;      
        unsigned int y;      
        unsigned int hit;    
    };

    struct ParsedShip
    {
        unsigned int type;                 
        std::vector<ParsedDeck> decks;     
    };

    struct ParsedBattlefield
    {
        unsigned int number;               
        std::vector<ParsedShip> ships;     
    };

    struct ParsedGameData
    {
        unsigned int elapsedSeconds;                   
        std::vector<ParsedBattlefield> battlefields;    
    };

    std::vector<std::string> SplitLine(const std::string& line)
    {
        std::vector<std::string> tokens;
        std::istringstream iss(line);
        std::string token;
        while (iss >> token)
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    bool IsValidCoordinate(unsigned int coord)
    {
        return coord >= 1 && coord <= 10;
    }

    bool IsValidHitFlag(unsigned int hit)
    {
        return hit == 0 || hit == 1;
    }

    bool IsValidShipType(unsigned int type)
    {
        return type >= 1 && type <= 4;
    }

    bool ParseDeckData(const std::string& deckStr, ParsedDeck& outDeck)
    {
        std::regex deckRegex(R"(^(\d+),(\d+),(\d+)$)");
        std::smatch matches;

        if (!std::regex_match(deckStr, matches, deckRegex))
        {
            return false;
        }

        try
        {
            unsigned int x = static_cast<unsigned int>(std::stoul(matches[1]));
            unsigned int y = static_cast<unsigned int>(std::stoul(matches[2]));
            unsigned int hit = static_cast<unsigned int>(std::stoul(matches[3]));

            if (!IsValidCoordinate(x) || !IsValidCoordinate(y) || !IsValidHitFlag(hit))
            {
                return false;
            }

            outDeck.x = x;
            outDeck.y = y;
            outDeck.hit = hit;
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool IsFileEmpty(const std::string& content)
    {
        return content.empty() || content.find_first_not_of(" \t\n\r") == std::string::npos;
    }

    bool ValidateAndParseFileContent(const std::string& content, ParsedGameData& outData)
    {
        if (IsFileEmpty(content))
        {
            return false;
        }

        std::istringstream stream(content);
        std::string line;
        bool hasElapsedSeconds = false;          
        unsigned int battlefieldNumber = 0;      
        ParsedBattlefield currentBattlefield;    
        ParsedShip currentShip;                  
        bool isParsingShip = false;              
        unsigned int lineNumber = 0;

        while (std::getline(stream, line))
        {
            ++lineNumber;

            // Пропускаем пустые строки
            if (line.empty())
            {
                continue;
            }

            size_t start = line.find_first_not_of(" \t\r\n");
            if (start == std::string::npos)
            {
                continue;
            }
            line = line.substr(start);

            auto tokens = SplitLine(line);
            if (tokens.empty())
            {
                continue;
            }

            if (tokens[0] == "elapsed-seconds")
            {
                if (hasElapsedSeconds)
                {
                    return false;
                }

                if (tokens.size() != 2)
                {
                    return false;
                }

                try
                {
                    outData.elapsedSeconds = static_cast<unsigned int>(std::stoul(tokens[1]));
                    hasElapsedSeconds = true;
                }
                catch (...)
                {
                    return false;
                }
            }

            else if (tokens[0] == "battlefield")
            {
                if (isParsingShip)
                {
                    return false;
                }

                if (tokens.size() != 2)
                {
                    return false;
                }

                try
                {
                    unsigned int num = static_cast<unsigned int>(std::stoul(tokens[1]));
                    if (num != ++battlefieldNumber)
                    {
                        return false;
                    }

                    if (battlefieldNumber > 1)
                    {
                        outData.battlefields.push_back(currentBattlefield);
                    }

                    currentBattlefield.number = num;
                    currentBattlefield.ships.clear();
                }
                catch (...)
                {
                    return false;
                }
            }
            else if (tokens[0] == "ship")
            {
                if (tokens.size() < 2)
                {
                    return false;
                }

                if (isParsingShip)
                {
                    currentBattlefield.ships.push_back(currentShip);
                    currentShip.decks.clear();
                }

                try
                {
                    unsigned int shipType = static_cast<unsigned int>(std::stoul(tokens[1]));
                    if (!IsValidShipType(shipType))
                    {
                        return false;
                    }

                    currentShip.type = shipType;
                    currentShip.decks.clear();

                    for (size_t i = 2; i < tokens.size(); ++i)
                    {
                        ParsedDeck deck;
                        if (!ParseDeckData(tokens[i], deck))
                        {
                            return false;
                        }
                        currentShip.decks.push_back(deck);
                    }

                    if (currentShip.decks.size() != currentShip.type)
                    {
                        return false;
                    }

                    isParsingShip = true;
                }
                catch (...)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        if (isParsingShip)
        {
            currentBattlefield.ships.push_back(currentShip);
        }

        if (battlefieldNumber > 0)
        {
            outData.battlefields.push_back(currentBattlefield);
        }

        if (!hasElapsedSeconds || battlefieldNumber == 0)
        {
            return false;
        }

        if (outData.battlefields.size() != 2)
        {
            return false;
        }

        return true;
    }

    bool BuildGameFromParsedData(const ParsedGameData& data, Game& outGame)
    {
        try
        {
            Game tempGame(battlefield::AutomaticMode, battlefield::AutomaticMode);

            tempGame.GetBattlefields().clear();

            for (const auto& parsedBf : data.battlefields)
            {
                
                battlefield::Battlefield newBf(battlefield::ManualMode);

                newBf.GetShips().clear();
                
                for (const auto& parsedShip : parsedBf.ships)
                {
                    std::list<logic::Cell> cells;
                    logic::ShipTypes shipType = static_cast<logic::ShipTypes>(parsedShip.type);

                    for (const auto& parsedDeck : parsedShip.decks)
                    {
                        
                        logic::Cell cell(parsedDeck.x, parsedDeck.y);
                        
                        if (parsedDeck.hit == 1)
                        {
                            cell.TakeHit();
                        }
                        cells.push_back(cell);
                    }

                    logic::Ship ship(cells, shipType);
                    newBf.GetShips().push_back(ship);
                }

                tempGame.GetBattlefields().push_back(newBf);
            }

            if (tempGame.GetBattlefields().size() != 2)
            {
                return false;
            }

            outGame = std::move(tempGame);
            return true;
        }
        catch (...)
        {
            return false;
        }
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

    std::string content = data.str();

    
    ParsedGameData parsedData;
    if (!ValidateAndParseFileContent(content, parsedData))
    {
        return false;
    }

    
    return BuildGameFromParsedData(parsedData, game);
}