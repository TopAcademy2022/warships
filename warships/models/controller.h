#pragma once


#include "i-database.h"
#include "game.h"

class Controller
{
private:
	IDatabase* _iDatabase;

	Game* _game;

public:
	Controller(IDatabase* IDatabase, Game* game);

	void StartGame();
};