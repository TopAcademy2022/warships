#pragma once


#include "controller.h"

class IUserInterface
{
private:
	Controller* _controller;

public:
	IUserInterface(IDatabase* iDatabase);

	Controller* GetController();

	virtual void PrintGameMenu() = 0;

	virtual void PrintGameBattleField() = 0;

	virtual void CreateNewGame() = 0;

	virtual void LoadGame() = 0;

	virtual void CreateNetworkGame() = 0;

	virtual void SetSettings() = 0;

	virtual void Exit() = 0;
};