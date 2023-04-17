#pragma once


#include <iostream>
#include "i-database.h"
#include "game.h"

class Controller
{
private:
	IDatabase* _IDatabase;

	Game* _game;

public:
	Controller(IDatabase* IDatabase, Game* game);

	void StartGame();
};