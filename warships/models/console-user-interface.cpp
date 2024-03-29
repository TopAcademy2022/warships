#include "console-user-interface.h"

void ConsoleUserInterface::PrintGameMenu()
{
	int menuSelection = 0;
	do
	{
		std::cout << "\n\t Warships game" << std::endl;
		std::cout << "\t Menu" << std::endl;
		std::cout << " 1. Create new game" << std::endl;
		std::cout << " 2. Load game" << std::endl;
		std::cout << " 3. Create network game" << std::endl;
		std::cout << " 4. Set settings" << std::endl;
		std::cout << " 5. Exit" << std::endl << std::endl;

		do
		{
			std::cout << " Select a menu item" << std::endl;
			std::cin >> menuSelection;

			if (!std::cin >> menuSelection)
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}

		} while (menuSelection < 1 || menuSelection > 5);

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
			break;
		}

	} while (menuSelection != 5);

}

void ConsoleUserInterface::CreateNewGame()
{
	
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