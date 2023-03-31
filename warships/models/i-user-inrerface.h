#pragma once


#include <string>
#include "controller.h"

class IUserInterface
{
private:
	Controller* _controller;

	unsigned int _countMenuElements;

	std::string _menuElements[];

public:
	IUserInterface(Controller* controller, unsigned int countMenuElements);

	void PrintGameMenu();

	void CreateNewGame();

	void LoadGame();

	void CreateNetworkGame();

	void SetSettings();

	void Exit();
};