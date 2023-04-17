#pragma once


#include "controller.h"

class IUserInterface
{
private:
	Controller* _controller;

public:
	IUserInterface(Controller* controller);

	virtual void PrintGameMenu() = 0;

	virtual void CreateNewGame() = 0;

	virtual void LoadGame() = 0;

	virtual void CreateNetworkGame() = 0;

	virtual void SetSettings() = 0;

	virtual void Exit() = 0;
};