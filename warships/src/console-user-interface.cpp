#include "console-user-interface.h"

#include <limits>
#include <memory>
#include <utility>

void ConsoleUserInterface::PrintGameMenu()
{
	while (true)
	{
		std::cout << "\n\t Warships game" << std::endl;
		std::cout << "\t Menu" << std::endl;
		std::cout << " 1. Create new game" << std::endl;
		std::cout << " 2. Load game" << std::endl;
		std::cout << " 3. Create network game" << std::endl;
		std::cout << " 4. Set settings" << std::endl;
		std::cout << " 5. Exit" << std::endl << std::endl;

		int menuSelection = 0;
		std::cout << " Select a menu item" << std::endl;

		if (!(std::cin >> menuSelection))
		{
			if (std::cin.eof())
			{
				return;
			}

			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << " Invalid menu item" << std::endl;
			continue;
		}

		if (menuSelection < 1 || menuSelection > 5)
		{
			std::cout << " Invalid menu item" << std::endl;
			continue;
		}

		switch (menuSelection)
		{
		case 1:
			this->CreateNewGame();
			break;
		case 2:
			this->LoadGame();
			break;
		case 3:
			this->CreateNetworkGame();
			break;
		case 4:
			this->SetSettings();
			break;
		case 5:
			this->Exit();
			return;
		}
	}
}

void ConsoleUserInterface::CreateNewGame()
{
	battlefield::ShipDeploymentMode firstPlayerInitShipsMode = battlefield::ShipDeploymentMode::AutomaticMode;
	battlefield::ShipDeploymentMode secondPlayerInitShipsMode = battlefield::ShipDeploymentMode::AutomaticMode;

	std::unique_ptr<Game> newGame = std::make_unique<Game>(firstPlayerInitShipsMode,
		secondPlayerInitShipsMode);
	this->GetController().InitGame(std::move(newGame));
	this->PrintGameBattleField();
}

void ConsoleUserInterface::PrintGameBattleField()
{
	Game* game = this->GetController().GetGame();
	if (game == nullptr)
	{
		std::cout << " The game has not been created" << std::endl;
		return;
	}

	const auto& battlefields = game->GetBattlefields();
	if(battlefields.empty())
	{
		std::cout << " The battlefield has not been created" << std::endl;
		return;
	}

	int playerNumber = 1;
	for(const auto& battlefield : battlefields)
	{
		std::cout << "\n Player " << playerNumber << " battlefield" << std::endl;
		for (const logic::Ship& ship : battlefield.GetShips())
		{

			std::cout << " " << static_cast<unsigned int>(ship.GetShipType()) << "-deck ship:";

			for (const logic::Cell& deck : ship.GetDecks())
			{
				std::cout << " (" << deck.GetPositionX() << ", " << deck.GetPositionY() << ")";
				if (deck.GetIsHit())
				{
					std::cout << " hit";
				}
		    }

			std::cout << std::endl;
		}
		playerNumber++;
	}
}

void ConsoleUserInterface::LoadGame()
{

}

void ConsoleUserInterface::CreateNetworkGame()
{

}

void ConsoleUserInterface::SetSettings()
{

}

void ConsoleUserInterface::Exit()
{
	std::cout << " We will be glad to see you again " << std::endl;
	std::cout << " Bye Bye " << std::endl;
}
