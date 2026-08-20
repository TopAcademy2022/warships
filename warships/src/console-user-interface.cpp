#include "console-user-interface.h"

#include <limits>
#include <memory>
#include <utility>
#include <string>
#include <cstdlib>
#include <cctype>

void ClearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void WaitEnter() {
	std::cout << " Press Enter to continue...";
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	std::cin.get();
}

void ConsoleUserInterface::PrintGameMenu()
{
	while (true)
	{
		ClearScreen();
		std::cout << "\n\t Warships game" << std::endl;
		std::cout << "\t Menu" << std::endl;
		std::cout << " 1. Create new game" << std::endl;
		std::cout << " 2. Load game" << std::endl;
		std::cout << " 3. Create network game" << std::endl;
		std::cout << " 4. Set settings" << std::endl;
		std::cout << " 5. Exit" << std::endl << std::endl;

		int menuSelection = 0;
		std::cout << " Select a menu item: ";

		if (!(std::cin >> menuSelection))
		{
			if (std::cin.eof()) return;
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << " Invalid menu item\n";
			WaitEnter();
			continue;
		}

		if (menuSelection < 1 || menuSelection > 5)
		{
			std::cout << " Invalid menu item\n";
			WaitEnter();
			continue;
		}

		switch (menuSelection)
		{
		case 1: this->CreateNewGame(); break;
		case 2: this->LoadGame(); break;
		case 3: this->CreateNetworkGame(); break;
		case 4: this->SetSettings(); break;
		case 5: this->Exit(); return;
		}
	}
}

void ConsoleUserInterface::CreateNewGame()
{
	battlefield::ShipDeploymentMode firstPlayerInitShipsMode = battlefield::ShipDeploymentMode::AutomaticMode;
	battlefield::ShipDeploymentMode secondPlayerInitShipsMode = battlefield::ShipDeploymentMode::AutomaticMode;

	std::unique_ptr<Game> newGame = std::make_unique<Game>(firstPlayerInitShipsMode, secondPlayerInitShipsMode);
	this->GetController().InitGame(std::move(newGame));

	this->RunLocalMatch();
}

void ConsoleUserInterface::RunLocalMatch()
{
	Game* game = this->GetController().GetGame();
	if (game == nullptr || game->GetBattlefields().size() < 2) return;

	auto it = game->GetBattlefields().begin();
	battlefield::Battlefield& p1Field = *it;
	std::advance(it, 1);
	battlefield::Battlefield& p2Field = *it;

	bool isPlayerOneTurn = true;
	bool isGameOver = false;

	while (!isGameOver)
	{
		ClearScreen();
		std::cout << "\n\t --- PLAYER " << (isPlayerOneTurn ? "1" : "2") << " TURN ---\n\n";

		battlefield::Battlefield& myField = isPlayerOneTurn ? p1Field : p2Field;
		battlefield::Battlefield& enemyField = isPlayerOneTurn ? p2Field : p1Field;

		std::cout << " ENEMY BOARD:\n";
		this->DrawBoard(enemyField, true);

		std::cout << "\n YOUR BOARD:\n";
		this->DrawBoard(myField, false);

		std::cout << "\n";
		unsigned int x, y;
		this->ReadCoordinatesSafely(x, y);

		battlefield::ShotResult result = enemyField.FireAt(x, y);

		std::cout << "\n Result: ";
		switch (result)
		{
		case battlefield::ShotResult::Miss:
			std::cout << "Miss! Turn goes to the opponent.\n";
			isPlayerOneTurn = !isPlayerOneTurn;
			break;
		case battlefield::ShotResult::Hit:
			std::cout << "HIT! You get another shot.\n";
			break;
		case battlefield::ShotResult::Sunk:
			std::cout << "SHIP SUNK! You get another shot.\n";
			break;
		case battlefield::ShotResult::Repeated:
			std::cout << "You already shot there! Try different coordinates.\n";
			break;
		case battlefield::ShotResult::Invalid:
			std::cout << "Coordinates are out of bounds!\n";
			break;
		case battlefield::ShotResult::Victory:
			std::cout << "VICTORY! All enemy ships are destroyed!\n";
			isGameOver = true;
			break;
		}
		WaitEnter();
	}
}

void ConsoleUserInterface::DrawBoard(const battlefield::Battlefield& field, bool isEnemy)
{
	std::cout << "    A B C D E F G H I J\n";
	for (unsigned int y = 0; y < 10; ++y)
	{
		if (y + 1 < 10) std::cout << "  " << y + 1 << " ";
		else std::cout << " " << y + 1 << " ";

		for (unsigned int x = 0; x < 10; ++x)
		{
			battlefield::CellState state = field.GetCellState(x, y);

			switch (state)
			{
			case battlefield::CellState::Water:
				std::cout << "~ ";
				break;
			case battlefield::CellState::IntactShip:
				if (isEnemy) std::cout << "~ ";
				else std::cout << "O ";
				break;
			case battlefield::CellState::Missed:
				std::cout << "* ";
				break;
			case battlefield::CellState::Hit:
				std::cout << "X ";
				break;
			}
		}
		std::cout << "\n";
	}
}

void ConsoleUserInterface::ReadCoordinatesSafely(unsigned int& outX, unsigned int& outY)
{
	std::string input;
	while (true)
	{
		std::cout << " Enter target coordinates (e.g. A5): ";
		std::cin >> input;

		if (input.length() < 2 || input.length() > 3)
		{
			std::cout << " Error: invalid format.\n";
			continue;
		}

		char letter = toupper(input[0]);
		if (letter < 'A' || letter > 'J')
		{
			std::cout << " Error: Letter must be A-J.\n";
			continue;
		}
		outX = letter - 'A';

		std::string numberStr = input.substr(1);
		try
		{
			int number = std::stoi(numberStr);
			if (number < 1 || number > 10)
			{
				std::cout << " Error: Number must be 1-10.\n";
				continue;
			}
			outY = number - 1;
			break;
		}
		catch (const std::exception&)
		{
			std::cout << " Error: Number must follow the letter.\n";
		}
	}
}

void ConsoleUserInterface::LoadGame() { std::cout << "\n Feature not available in this version.\n"; WaitEnter(); }
void ConsoleUserInterface::CreateNetworkGame() { std::cout << "\n Feature not available in this version.\n"; WaitEnter(); }
void ConsoleUserInterface::SetSettings() { std::cout << "\n Feature not available in this version.\n"; WaitEnter(); }

void ConsoleUserInterface::PrintGameBattleField() {}

void ConsoleUserInterface::Exit()
{
	std::cout << "\n We will be glad to see you again \n";
	std::cout << " Bye Bye \n";
}