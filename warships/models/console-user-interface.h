#pragma once


#include "i-user-interface.h"

class ConsoleUserInterface : public IUserInterface
{
public:
	ConsoleUserInterface(Controller* controller) : IUserInterface(controller) {};

	void PrintGameMenu() override;

	void CreateNewGame() override;

	void LoadGame() override;

	void CreateNetworkGame() override;

	void SetSettings() override;

	void Exit() override;
};