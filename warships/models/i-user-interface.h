#pragma once


#include <string>
#include "controller.h"

class IUserInterface
{
private:
	Controller* _controller;

public:
	IUserInterface(Controller* controller);

	void PrintGameMenu();

	void CreateNewGame();

	void LoadGame();

	void CreateNetworkGame();

	void SetSettings();

	void Exit();
};