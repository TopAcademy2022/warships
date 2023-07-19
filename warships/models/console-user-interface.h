#pragma once

#include <iostream>
#include "i-user-interface.h"
#include "game.h"

class ConsoleUserInterface : public IUserInterface
{
private:

	void CreateNewGame() override;

	void LoadGame() override;

	void CreateNetworkGame() override;

	void SetSettings() override;

	void Exit() override;

public:
	ConsoleUserInterface(Controller* controller) : IUserInterface(controller) {};

	void PrintGameMenu() override;

};